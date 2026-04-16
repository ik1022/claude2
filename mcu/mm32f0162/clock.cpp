// MM32F0162 clock initialisation.
// Configures HSI (8 MHz) with PLL to reach the target system clock.
//
// !! Adjust PLL multiplier and bus dividers using the MM32F0162 datasheet.
//    The register writes below are placeholders. !!

#include "hal/clock.hpp"
#include "mcu/mm32f0162/reg/clock.hpp"

namespace hal
{
    namespace clock
    {

        void init()
        {
            // Example: HSI (8 MHz) × PLL × 6 = 48 MHz
            // Exact register bit-fields must be verified against the MM32F0162 RM.

            // 1. Enable HSI and wait for it to stabilise
            RCC.CR |= (1u << 0); // HSION
            while (!(RCC.CR & (1u << 1)))
            {
            }                    // wait HSIRDY

            // 2. Configure PLL (HSI/2 as source, × 6)
            //    CFGR bits [21:18] = PLLMUL, [16] = PLLSRC (0=HSI/2)
            RCC.CFGR = (RCC.CFGR & ~(0xFu << 18)) | (0x4u << 18); // TODO: verify multiplier field

            // 3. Enable PLL and wait
            RCC.CR |= (1u << 24); // PLLON
            while (!(RCC.CR & (1u << 25)))
            {
            }                     // wait PLLRDY

            // 4. Select PLL as system clock
            RCC.CFGR = (RCC.CFGR & ~0x3u) | 0x2u; // SW = PLL
            while ((RCC.CFGR & (0x3u << 2)) != (0x2u << 2))
            {
            }                                     // wait SWS
        }

    } // namespace clock
} // namespace hal
