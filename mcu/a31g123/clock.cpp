// A31G123 clock initialisation.
// Configures HSIOSC (internal 32 MHz RC) as the system clock.
//
// !! Adjust CLKSRCR / CLKDIVR values using the ABOV A31G123 datasheet.
//    The register writes below are placeholders. !!

#include "hal/clock.hpp"
#include "mcu/a31g123/reg/clock.hpp"

namespace hal
{
    namespace clock
    {

        void init()
        {
            // Example: select HSIOSC, no divider → 32 MHz system clock.
            // Refer to ABOV A31G123 CG chapter for exact bit-field definitions.
            // CG.CLKSRCR = 0x0000'0001u; // TODO: verify — select HSIOSC
            // CG.CLKDIVR = 0x0000'0000u; // TODO: verify — divider = /1
        }

    } // namespace clock
} // namespace hal
