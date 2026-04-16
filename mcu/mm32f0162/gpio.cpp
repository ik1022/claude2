// MM32F0162 GPIO HAL implementation.
// !! Verify register bit definitions against the MindMotion MM32F0162 datasheet. !!

#include "hal/gpio.hpp"
#include "mcu/mm32f0162/reg/clock.hpp"
#include "mcu/mm32f0162/reg/gpio.hpp"

namespace hal
{
    namespace gpio
    {

        // Map Port enum → AHBENR bit
        static constexpr uint32_t port_clock_bits[] = {
          AhbEn::GPIOA, AhbEn::GPIOB, AhbEn::GPIOC, AhbEn::GPIOD, 0u, AhbEn::GPIOF,
        };

        void enable_clock(Port port) { RCC.AHBENR |= port_clock_bits[static_cast<uint8_t>(port)]; }

        void configure(Port port, Pin pin, Mode mode, Pull pull)
        {
            GpioPort &p   = gpio_port(static_cast<uint32_t>(port));
            uint32_t  idx = static_cast<uint32_t>(pin);

            // MODER: 00=Input 01=Output 10=AF 11=Analog
            uint32_t moder_val = 0u;
            switch (mode)
            {
                case Mode::Input:
                case Mode::Analog:
                    moder_val = GpioPort::MODE_INPUT;
                    break;
                case Mode::OutputPushPull:
                case Mode::OutputOpenDrain:
                    moder_val = GpioPort::MODE_OUTPUT;
                    break;
                case Mode::AltFunc:
                    moder_val = GpioPort::MODE_AF;
                    break;
            }
            p.MODER = (p.MODER & ~(0x3u << (idx * 2u))) | (moder_val << (idx * 2u));

            // OTYPER: 0=push-pull 1=open-drain
            if (mode == Mode::OutputOpenDrain)
            {
                p.OTYPER |= (1u << idx);
            }
            else
            {
                p.OTYPER &= ~(1u << idx);
            }

            // PUPDR: 00=None 01=Pull-Up 10=Pull-Down
            uint32_t pupdr_val = 0u;
            switch (pull)
            {
                case Pull::None:
                    pupdr_val = GpioPort::PULL_NONE;
                    break;
                case Pull::Up:
                    pupdr_val = GpioPort::PULL_UP;
                    break;
                case Pull::Down:
                    pupdr_val = GpioPort::PULL_DOWN;
                    break;
            }
            p.PUPDR = (p.PUPDR & ~(0x3u << (idx * 2u))) | (pupdr_val << (idx * 2u));
        }

        void set(Port port, Pin pin)
        {
            gpio_port(static_cast<uint32_t>(port)).BSRR = (1u << static_cast<uint32_t>(pin));
        }

        void clear(Port port, Pin pin)
        {
            gpio_port(static_cast<uint32_t>(port)).BSRR = (1u << (static_cast<uint32_t>(pin) + 16u));
        }

        void toggle(Port port, Pin pin)
        {
            GpioPort &p  = gpio_port(static_cast<uint32_t>(port));
            p.ODR       ^= (1u << static_cast<uint32_t>(pin));
        }

        bool read(Port port, Pin pin)
        {
            return (gpio_port(static_cast<uint32_t>(port)).IDR >> static_cast<uint32_t>(pin)) & 1u;
        }

    } // namespace gpio
} // namespace hal
