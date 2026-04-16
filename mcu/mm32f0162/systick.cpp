// MM32F0162 SysTick HAL implementation.
// Uses the ARM Cortex-M0 SysTick timer (common to all CM0 cores).

#include "hal/systick.hpp"
#include "core_cm0/systick.hpp"

#ifndef MCU_CLOCK_HZ
#error "MCU_CLOCK_HZ must be defined (set in cmake/target-mm32f0162.cmake)"
#endif

namespace hal
{
    namespace systick
    {

        static volatile uint32_t s_millis = 0u;

        void init(uint32_t ticks_per_second) { SYSTICK.start(MCU_CLOCK_HZ / ticks_per_second); }

        uint32_t millis() { return s_millis; }

        void delay_ms(uint32_t ms)
        {
            uint32_t end = s_millis + ms;
            while (s_millis < end)
            {
                asm volatile("wfi");
            }
        }

    } // namespace systick
} // namespace hal

// Override the weak SYSTICK_handler from core_cm0/handlers.cpp.
// __attribute__((used)) prevents LTO + --gc-sections from removing this ISR.
extern "C" __attribute__((used)) void SYSTICK_handler() { hal::systick::s_millis++; }
