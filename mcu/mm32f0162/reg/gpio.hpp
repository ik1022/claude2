#pragma once
// MindMotion MM32F0162 GPIO peripheral registers
// AHB-based GPIO, compatible with STM32F0 register layout.
//
// !! Verify all register offsets and bit definitions against the
//    MindMotion MM32F0162 datasheet before use. !!

#include <cstdint>

struct GpioPort
{
    volatile uint32_t MODER;   // 0x00  Mode Register        (2 bits/pin)
    volatile uint32_t OTYPER;  // 0x04  Output Type Register (1 bit/pin)
    volatile uint32_t OSPEEDR; // 0x08  Output Speed Register
    volatile uint32_t PUPDR;   // 0x0C  Pull-Up/Down Register (2 bits/pin)
    volatile uint32_t IDR;     // 0x10  Input Data Register
    volatile uint32_t ODR;     // 0x14  Output Data Register
    volatile uint32_t BSRR;    // 0x18  Bit Set/Reset Register (upper half: reset, lower: set)
    volatile uint32_t LCKR;    // 0x1C  Lock Register
    volatile uint32_t AFRL;    // 0x20  Alternate Function Low  (pins 0-7)
    volatile uint32_t AFRH;    // 0x24  Alternate Function High (pins 8-15)
    volatile uint32_t BRR;     // 0x28  Bit Reset Register

    // MODER values per pin pair
    static constexpr uint32_t MODE_INPUT  = 0x0u;
    static constexpr uint32_t MODE_OUTPUT = 0x1u;
    static constexpr uint32_t MODE_AF     = 0x2u;
    static constexpr uint32_t MODE_ANALOG = 0x3u;

    // PUPDR values
    static constexpr uint32_t PULL_NONE = 0x0u;
    static constexpr uint32_t PULL_UP   = 0x1u;
    static constexpr uint32_t PULL_DOWN = 0x2u;

    void set_mode(uint32_t pin, uint32_t mode) { MODER = (MODER & ~(0x3u << (pin * 2u))) | (mode << (pin * 2u)); }

    void set_pull(uint32_t pin, uint32_t pull) { PUPDR = (PUPDR & ~(0x3u << (pin * 2u))) | (pull << (pin * 2u)); }
};

// GPIO base addresses — verify with MM32F0162 datasheet memory map
inline GpioPort &GPIOA = *reinterpret_cast<GpioPort *>(0x48000000u);
inline GpioPort &GPIOB = *reinterpret_cast<GpioPort *>(0x48000400u);
inline GpioPort &GPIOC = *reinterpret_cast<GpioPort *>(0x48000800u);
inline GpioPort &GPIOD = *reinterpret_cast<GpioPort *>(0x48000C00u);
inline GpioPort &GPIOF = *reinterpret_cast<GpioPort *>(0x48001400u);

inline GpioPort &gpio_port(uint32_t idx)
{
    constexpr uint32_t bases[] = {
      0x48000000u, // A
      0x48000400u, // B
      0x48000800u, // C
      0x48000C00u, // D
      0x48001000u, // E (reserved/absent on some packages)
      0x48001400u, // F
    };
    return *reinterpret_cast<GpioPort *>(bases[idx]);
}
