#pragma once
// ABOV A31G123 clock / power-control registers
//
// !! Verify all register offsets and bit definitions against the
//    ABOV A31G123 datasheet before use. !!

#include <cstdint>

struct Cg
{                              // Clock Gate / System Clock control
    volatile uint32_t CLKSRCR; // 0x00  Clock Source Register
    volatile uint32_t CLKDIVR; // 0x04  Clock Divider Register
    volatile uint32_t CLKENR0; // 0x08  Clock Enable Register 0
    volatile uint32_t CLKENR1; // 0x0C  Clock Enable Register 1
    volatile uint32_t RSTDBCR; // 0x10  Reset/Debounce Control Register
    volatile uint32_t STCR;    // 0x14  System Timer Control Register
    volatile uint32_t WUTR;    // 0x18  Wake-Up Timer Register
    volatile uint32_t LVICR;   // 0x1C  LVI Control Register
    volatile uint32_t PLLCR;   // 0x20  PLL Control Register
    volatile uint32_t PLLSTR;  // 0x24  PLL Status Register
};

// Clock generator base address — verify with A31G123 datasheet
inline Cg &CG = *reinterpret_cast<Cg *>(0x40000000u);

// Peripheral clock enable bits in CLKENR0 (examples — verify with datasheet)
namespace ClkEn0
{
    static constexpr uint32_t PA      = (1u << 0);
    static constexpr uint32_t PB      = (1u << 1);
    static constexpr uint32_t PC      = (1u << 2);
    static constexpr uint32_t PD      = (1u << 3);
    static constexpr uint32_t PE      = (1u << 4);
    static constexpr uint32_t PF      = (1u << 5);
    static constexpr uint32_t TIMER10 = (1u << 8);
    static constexpr uint32_t UART0   = (1u << 16);
    static constexpr uint32_t UART1   = (1u << 17);
    static constexpr uint32_t I2C0    = (1u << 20);
}
