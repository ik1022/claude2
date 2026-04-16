#pragma once
// MindMotion MM32F0162 RCC (Reset and Clock Control) registers
// Compatible with STM32F0 RCC register layout.
//
// !! Verify all register offsets and bit definitions against the
//    MindMotion MM32F0162 datasheet before use. !!

#include <cstdint>

struct Rcc
{
    volatile uint32_t CR;       // 0x00  Clock Control Register
    volatile uint32_t CFGR;     // 0x04  Clock Configuration Register
    volatile uint32_t CIR;      // 0x08  Clock Interrupt Register
    volatile uint32_t APB2RSTR; // 0x0C  APB2 Peripheral Reset Register
    volatile uint32_t APB1RSTR; // 0x10  APB1 Peripheral Reset Register
    volatile uint32_t AHBENR;   // 0x14  AHB Peripheral Clock Enable Register
    volatile uint32_t APB2ENR;  // 0x18  APB2 Peripheral Clock Enable Register
    volatile uint32_t APB1ENR;  // 0x1C  APB1 Peripheral Clock Enable Register
    volatile uint32_t BDCR;     // 0x20  Backup Domain Control Register
    volatile uint32_t CSR;      // 0x24  Control/Status Register
    volatile uint32_t AHBRSTR;  // 0x28  AHB Peripheral Reset Register
    volatile uint32_t CFGR2;    // 0x2C  Clock Configuration Register 2
    volatile uint32_t CFGR3;    // 0x30  Clock Configuration Register 3
    volatile uint32_t CR2;      // 0x34  Clock Control Register 2
};

// RCC base address — verify with MM32F0162 datasheet
inline Rcc &RCC = *reinterpret_cast<Rcc *>(0x40021000u);

// AHBENR bit definitions (GPIO clocks)
namespace AhbEn
{
    static constexpr uint32_t GPIOA = (1u << 17);
    static constexpr uint32_t GPIOB = (1u << 18);
    static constexpr uint32_t GPIOC = (1u << 19);
    static constexpr uint32_t GPIOD = (1u << 20);
    static constexpr uint32_t GPIOF = (1u << 22);
    static constexpr uint32_t DMA1  = (1u << 0);
}

// APB2ENR bit definitions
namespace Apb2En
{
    static constexpr uint32_t SYSCFG = (1u << 0);
    static constexpr uint32_t ADC1   = (1u << 9);
    static constexpr uint32_t TIM1   = (1u << 11);
    static constexpr uint32_t SPI1   = (1u << 12);
    static constexpr uint32_t USART1 = (1u << 14);
    static constexpr uint32_t TIM16  = (1u << 17);
    static constexpr uint32_t TIM17  = (1u << 18);
}

// APB1ENR bit definitions
namespace Apb1En
{
    static constexpr uint32_t TIM3   = (1u << 1);
    static constexpr uint32_t TIM14  = (1u << 8);
    static constexpr uint32_t WWDG   = (1u << 11);
    static constexpr uint32_t I2C1   = (1u << 21);
    static constexpr uint32_t USART2 = (1u << 17);
    static constexpr uint32_t PWR    = (1u << 28);
}
