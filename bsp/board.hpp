#pragma once
// Board Support Package interface.
// Each board provides a board.cpp that implements bsp::init() and
// defines the led:: constants for the on-board LED location.

#include "hal/gpio.hpp"

namespace bsp
{

    // Initialise all board-level hardware:
    //   - system clock
    //   - SysTick (1 ms tick)
    //   - LED GPIO
    void init();

    namespace led
    {
        extern const hal::gpio::Port PORT;
        extern const hal::gpio::Pin  PIN;
    } // namespace led

} // namespace bsp
