cmake_minimum_required(VERSION 3.21)

if(NOT DEFINED TARGET_MCU)
    message(FATAL_ERROR
        "TARGET_MCU is not set.\n"
        "Use: cmake -DTARGET_MCU=A31G123 ...\n"
        "  or cmake -DTARGET_MCU=MM32F0162 ..."
    )
endif()

project(firmware LANGUAGES C CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# All supported MCUs are Cortex-M0; defined here once rather than per-target file
set(MCU_CPU_OPTIONS -mthumb -mcpu=cortex-m0)

# Load MCU-specific settings (linker script, clock, source lists)
string(TOLOWER "${TARGET_MCU}" _mcu_lower)
include(cmake/target-${_mcu_lower}.cmake)

# ── Optimization flags per build type ──────────────────────────────────────
set(CMAKE_C_FLAGS_DEBUG   "-Og -g -DDEBUG")
set(CMAKE_CXX_FLAGS_DEBUG "-Og -g -DDEBUG")
set(CMAKE_C_FLAGS_RELEASE   "-Os -g -flto -DNDEBUG")
set(CMAKE_CXX_FLAGS_RELEASE "-Os -g -flto -DNDEBUG")

# ── Compiler options ────────────────────────────────────────────────────────
add_compile_options(
    ${MCU_CPU_OPTIONS}

    $<$<COMPILE_LANGUAGE:C>:-std=c11>
    $<$<COMPILE_LANGUAGE:CXX>:-std=c++17>

    # C++ bare-metal: disable features that require runtime support
    $<$<COMPILE_LANGUAGE:CXX>:-fno-exceptions>
    $<$<COMPILE_LANGUAGE:CXX>:-fno-rtti>
    $<$<COMPILE_LANGUAGE:CXX>:-fno-use-cxa-atexit>
    $<$<COMPILE_LANGUAGE:CXX>:-fno-threadsafe-statics>
    $<$<COMPILE_LANGUAGE:CXX>:-fms-extensions>

    -fstrict-volatile-bitfields   # required for hardware register bit-fields
    -ffunction-sections
    -fdata-sections

    -Wall -Wextra -Werror
    -Wcast-align
    -Wconversion
    -Wsign-conversion
    -Wold-style-cast
    -Wshadow
    -pedantic
)

# Root is the include root so all headers are referenced from project root
include_directories(${CMAKE_SOURCE_DIR})

# ── Layer 1: core_cm0 ── ARM Cortex-M0 아키텍처 ────────────────────────────
add_library(core_cm0 OBJECT
    core_cm0/stack.cpp
    core_cm0/startup.cpp
    core_cm0/handlers.cpp
)

# ── Layer 2: hal ── MCU-독립 인터페이스 (헤더 전용) ──────────────────────────
add_library(hal INTERFACE)

# ── Layer 3: mcu ── 실리콘별 HAL 구현 ──────────────────────────────────────
add_library(mcu OBJECT ${MCU_SOURCES})
target_compile_definitions(mcu
    PRIVATE ${MCU_DEFINE}                # MCU 식별자: mcu 계층 내부에서만 사용
    PUBLIC  MCU_CLOCK_HZ=${MCU_CLOCK_HZ} # 클럭: bsp/app에서도 참조 가능
)
target_link_libraries(mcu PUBLIC core_cm0 hal)

# ── Layer 4: bsp ── 보드별 핀 배선 ────────────────────────────────────────
add_library(bsp OBJECT ${MCU_BSP_SOURCES})
target_link_libraries(bsp PUBLIC mcu)

# ── Layer 5: firmware ── 애플리케이션 ─────────────────────────────────────
add_executable(${PROJECT_NAME} app/main.cpp)
# CMake does not propagate OBJECT file inclusion through OBJECT library chains,
# so each layer must be listed explicitly to guarantee all objects are linked.
# Usage requirements (include dirs, compile defs) still flow transitively
# through the bsp → mcu → core_cm0/hal hierarchy declared above.
target_link_libraries(${PROJECT_NAME} PRIVATE core_cm0 mcu bsp)

target_link_options(${PROJECT_NAME} PRIVATE
    ${MCU_CPU_OPTIONS}
    -T${MCU_LINKER_SCRIPT}
    -nostartfiles
    -nostdlib
    -Wl,--gc-sections
    -Wl,-Map=${CMAKE_BINARY_DIR}/${PROJECT_NAME}.map
    -Wl,--no-warn-rwx-segments
)

# libgcc provides compiler runtime helpers (integer division, soft-float, etc.)
# that the compiler may emit even with -nostdlib.
target_link_libraries(${PROJECT_NAME} PRIVATE gcc)

set_property(TARGET ${PROJECT_NAME} PROPERTY LINK_DEPENDS ${MCU_LINKER_SCRIPT})

# ── Post-build artifacts ────────────────────────────────────────────────────
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_OBJCOPY} -Oihex  $<TARGET_FILE:${PROJECT_NAME}> ${PROJECT_NAME}.hex
    COMMAND ${CMAKE_OBJDUMP} -S      $<TARGET_FILE:${PROJECT_NAME}> > ${PROJECT_NAME}.lst
    COMMAND ${CMAKE_NM} -C -l -n -S  $<TARGET_FILE:${PROJECT_NAME}> > ${PROJECT_NAME}.sym
    COMMAND ${CMAKE_SIZE} --format=berkeley $<TARGET_FILE:${PROJECT_NAME}>
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
)
