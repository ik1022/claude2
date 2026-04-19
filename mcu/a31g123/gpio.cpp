// A31G123 GPIO HAL implementation.
// !! Verify register bit definitions against the ABOV A31G123 datasheet. !!

#include "hal/gpio.hpp"
#include "mcu/a31g123/reg/clock.hpp"
#include "mcu/a31g123/reg/gpio.hpp"

namespace hal
{
    namespace gpio
    {

        // Map Port enum → ClkEn0 bit
        static constexpr uint32_t port_clock_bits[] = {
          PPCLK1::PACLKE, PPCLK1::PBCLKE, PPCLK1::PCCLKE, PPCLK1::PDCLKE, PPCLK1::PECLKE, PPCLK1::PFCLKE,
        };

        void enable_clock(Port port) { SCUCG.PPCLKEN1 |= port_clock_bits[static_cast<uint8_t>(port)]; }

        void configure(Port port, Pin pin, Mode mode, Pull pull)
        {
            GpioPort &p    = gpio_port(static_cast<uint32_t>(port));
            uint32_t  idx  = static_cast<uint32_t>(pin);
            uint32_t  mask = 0x3u << (idx * 2u);

            // MOD register: 00=Input 01=Push-Pull output 10=Open-Drain output
            uint32_t mod_val = 0u;
            switch (mode)
            {
                case Mode::Input:
                    mod_val = 0x0u;
                    break;
                case Mode::OutputPushPull:
                    mod_val = 0x1u;
                    break;
                case Mode::OutputOpenDrain:
                    mod_val = 0x1u;
                    break;
                case Mode::Analog:
                    mod_val = 0x0u;
                    break; // TODO: verify
                case Mode::AltFunc:
                    mod_val = 0x3u;
                    break; // TODO: verify
            }
            p.MOD = (p.MOD & ~mask) | (mod_val << (idx * 2u));

            // PUPD register: 00=Floating 01=Pull-Up 10=Pull-Down
            uint32_t pupd_val = 0u;
            switch (pull)
            {
                case Pull::None:
                    pupd_val = 0x0u;
                    break;
                case Pull::Up:
                    pupd_val = 0x1u;
                    break;
                case Pull::Down:
                    pupd_val = 0x2u;
                    break;
            }
            p.PUPD = (p.PUPD & ~mask) | (pupd_val << (idx * 2u));
        }

        void set(Port port, Pin pin)
        {
            gpio_port(static_cast<uint32_t>(port)).BSR = (1u << static_cast<uint32_t>(pin));
        }

        void clear(Port port, Pin pin)
        {
            gpio_port(static_cast<uint32_t>(port)).BCR = (1u << static_cast<uint32_t>(pin));
        }

        void toggle(Port port, Pin pin)
        {
            GpioPort &p  = gpio_port(static_cast<uint32_t>(port));
            p.OUTR      ^= (1u << static_cast<uint32_t>(pin));
        }

        bool read(Port port, Pin pin)
        {
            return (gpio_port(static_cast<uint32_t>(port)).INDR >> static_cast<uint32_t>(pin)) & 1u;
        }

    } // namespace gpio
} // namespace hal
