#pragma once
// ABOV A31G123 clock / power-control registers
//
// !! Verify all register offsets and bit definitions against the
//    ABOV A31G123 datasheet before use. !!

#include <cstdint>

struct SCUCG_Type
{                                  // System Control Unit: Clock Generation (SCUCG)
    volatile uint32_t SCCR;        // 0x00		System Clock Control Register
    volatile uint32_t CLKSRCR;     // 0x04		Clock Source Control Register
    volatile uint32_t SCDIVR1;     // 0x08		System Clock Divide Register 1
    volatile uint32_t SCDIVR2;     // 0x0C		System Clock Divide Register 2
    volatile uint32_t CLKOCR;      // 0x10		Clock Output Control Register
    volatile uint32_t CMONCR;      // 0x14		Clock Monitoring Control Register
    volatile uint32_t reserve0[2]; //
    volatile uint32_t PPCLKEN1;    // 0x20		Peripheral Clock Enable Register 1
    volatile uint32_t PPCLKEN2;    // 0x24		Peripheral Clock Enable Register 2
    volatile uint32_t reserve1[6]; //
    volatile uint32_t PPCLKSR;     // 0x40		Peripheral Clock Selection Register
    volatile uint32_t reserve2[7]; //
    volatile uint32_t PPRST1;      // 0x60		Peripheral Reset Register 1
    volatile uint32_t PPRST2;      // 0x64		Peripheral Reset Register 2
    volatile uint32_t reserve3[6]; //
    volatile uint32_t XTFLSR;      // 0x80		X-tal Filter Selection Register
};

// Clock generator base address — verify with A31G123 datasheet
inline SCUCG_Type &SCUCG = *reinterpret_cast<SCUCG_Type *>(0x40001800u);

// Peripheral clock enable bits in CLKENR0 (examples — verify with datasheet)
namespace PPCLK1
{
    static constexpr uint32_t PACLKE  = (1u << 0);
    static constexpr uint32_t PBCLKE  = (1u << 1);
    static constexpr uint32_t PCCLKE  = (1u << 2);
    static constexpr uint32_t PDCLKE  = (1u << 3);
    static constexpr uint32_t PECLKE  = (1u << 4);
    static constexpr uint32_t PFCLKE  = (1u << 5);
    static constexpr uint32_t T13CLKE = (1u << 8);
    static constexpr uint32_t T14CLKE = (1u << 9);
    static constexpr uint32_t T15CLKE = (1u << 10);
    static constexpr uint32_t T16CLKE = (1u << 11);
    static constexpr uint32_t T10CLKE = (1u << 16);
    static constexpr uint32_t T11CLKE = (1u << 17);
    static constexpr uint32_t T12CLKE = (1u << 18);
    static constexpr uint32_t T30CLKE = (1u << 19);
    static constexpr uint32_t T20CLKE = (1u << 20);
    static constexpr uint32_t T21CLKE = (1u << 21);
}

namespace PPCLK2
{
    static constexpr uint32_t UST10CLKE = (1u << 0);
    static constexpr uint32_t UST11CLKE = (1u << 1);
    static constexpr uint32_t UT0CLKE   = (1u << 2);
    static constexpr uint32_t UT1CLKE   = (1u << 3);
    static constexpr uint32_t UST12CLKE = (1u << 4);
    static constexpr uint32_t UST13CLKE = (1u << 5);
    static constexpr uint32_t I2C0CLKE  = (1u << 6);
    static constexpr uint32_t I2C1CLKE  = (1u << 7);
    static constexpr uint32_t I2C2CLKE  = (1u << 8);
    static constexpr uint32_t ADCLKE    = (1u << 10);
    static constexpr uint32_t CRCLKE    = (1u << 12);
    static constexpr uint32_t LCDCLKE   = (1u << 13);
    static constexpr uint32_t WTCLKE    = (1u << 16);
    static constexpr uint32_t WDTCLKE   = (1u << 17);
    static constexpr uint32_t LVICLKE   = (1u << 18);
    static constexpr uint32_t FMCLKE    = (1u << 19);
}
