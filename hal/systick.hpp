#pragma once
// MCU-agnostic SysTick HAL interface.
// Implementations live in hal/<mcu>/systick.cpp.

#include <cstdint>

namespace hal
{
    namespace systick
    {

        // Initialise SysTick to fire every (cpu_hz / ticks_per_second) cycles.
        // Must be called after clock initialisation.
        // Example: init(1000) → 1 ms tick at whatever MCU_CLOCK_HZ is.
        void init(uint32_t ticks_per_second);

        // Milliseconds since init() was called (wraps at ~49 days).
        uint32_t millis();

        // Blocking delay.
        void delay_ms(uint32_t ms);

    } // namespace systick
} // namespace hal
