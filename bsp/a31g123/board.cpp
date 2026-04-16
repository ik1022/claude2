// Board Support Package for A31G123 target board.
// LED is on PF7 — adjust PORT and PIN to match your hardware.

#include "bsp/board.hpp"
#include "hal/clock.hpp"
#include "hal/gpio.hpp"
#include "hal/systick.hpp"

namespace bsp
{

    const hal::gpio::Port led::PORT = hal::gpio::Port::PF;
    const hal::gpio::Pin  led::PIN  = hal::gpio::Pin::P7;

    void init()
    {
        hal::clock::init();
        hal::systick::init(1000); // 1 ms tick

        hal::gpio::enable_clock(led::PORT);
        hal::gpio::configure(led::PORT, led::PIN, hal::gpio::Mode::OutputPushPull);
    }

} // namespace bsp
