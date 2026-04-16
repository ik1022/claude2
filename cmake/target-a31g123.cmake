# ── ABOV A31G123 ──────────────────────────────────────────────────────────
# Cortex-M0 | 64 KB Flash @ 0x00000000 | 4 KB SRAM @ 0x20000000 | 32 MHz max

set(MCU_LINKER_SCRIPT "${CMAKE_SOURCE_DIR}/mcu/a31g123/ld/a31g123.ld")
set(MCU_DEFINE A31G123)

# MCU_CLOCK_HZ: default HSIOSC. Override with -DMCU_CLOCK_HZ=<hz> if needed.
if(NOT DEFINED MCU_CLOCK_HZ)
    set(MCU_CLOCK_HZ 2500000)
endif()

# mcu layer: MCU-specific IRQ vectors + HAL implementation
set(MCU_SOURCES
    ${CMAKE_SOURCE_DIR}/mcu/a31g123/handlers.cpp
    ${CMAKE_SOURCE_DIR}/mcu/a31g123/gpio.cpp
    ${CMAKE_SOURCE_DIR}/mcu/a31g123/systick.cpp
    ${CMAKE_SOURCE_DIR}/mcu/a31g123/clock.cpp
)

# bsp layer: board-specific wiring
set(MCU_BSP_SOURCES
    ${CMAKE_SOURCE_DIR}/bsp/a31g123/board.cpp
)
