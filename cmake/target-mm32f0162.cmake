# ── MindMotion MM32F0162 ───────────────────────────────────────────────────
# Cortex-M0 | 64 KB Flash @ 0x08000000 | 8 KB SRAM @ 0x20000000 | 72 MHz max

set(MCU_LINKER_SCRIPT "${CMAKE_SOURCE_DIR}/mcu/mm32f0162/ld/mm32f0162.ld")
set(MCU_DEFINE MM32F0162)

# MCU_CLOCK_HZ: default HSI (48 MHz). Override with -DMCU_CLOCK_HZ=<hz> if needed.
if(NOT DEFINED MCU_CLOCK_HZ)
    set(MCU_CLOCK_HZ 48000000)
endif()

# mcu layer: MCU-specific IRQ vectors + HAL implementation
set(MCU_SOURCES
    ${CMAKE_SOURCE_DIR}/mcu/mm32f0162/handlers.cpp
    ${CMAKE_SOURCE_DIR}/mcu/mm32f0162/gpio.cpp
    ${CMAKE_SOURCE_DIR}/mcu/mm32f0162/systick.cpp
    ${CMAKE_SOURCE_DIR}/mcu/mm32f0162/clock.cpp
)

# bsp layer: board-specific wiring
set(MCU_BSP_SOURCES
    ${CMAKE_SOURCE_DIR}/bsp/mm32f0162/board.cpp
)
