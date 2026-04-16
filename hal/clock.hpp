#pragma once

// MCU-agnostic clock HAL interface.
// Implementations live in hal/<mcu>/clock.cpp.
//
// init() configures the system clock to MCU_CLOCK_HZ (defined by cmake/target-*.cmake).
// Call this first in main_app() before any peripheral initialisation.

namespace hal
{
    namespace clock
    {

        void init();

    } // namespace clock
} // namespace hal
