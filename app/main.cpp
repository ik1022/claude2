// Application entry point — MCU-agnostic.
// Called by RESET_handler() in core_cm0/startup.cpp after C/C++ runtime init.

#include "bsp/board.hpp"
#include "hal/gpio.hpp"
#include "hal/systick.hpp"

static volatile unsigned &pfmod   = *reinterpret_cast<unsigned *>(0x30000500UL);
static volatile unsigned &pfout   = *reinterpret_cast<unsigned *>(0x30000518UL);
static volatile unsigned &clkreg1 = *reinterpret_cast<unsigned *>(0x40001A00UL);
static volatile unsigned &clkreg2 = *reinterpret_cast<unsigned *>(0x40001820UL);

volatile int j = 0;

extern "C" void main_app()
{
    bsp::init();

    clkreg1 = 0x5A690000 | (37 << 10) | (26 << 4);
    clkreg2 = 0x20;

    pfmod = 0x4000;

    while (true)
    {
        // hal::gpio::toggle(bsp::led::PORT, bsp::led::PIN);
        pfout ^= 0x80;
        j++;
        hal::systick::delay_ms(500);
    }
}

extern "C" void WT_handler(void)
{
    volatile static int k = 0;
    k++;
}
