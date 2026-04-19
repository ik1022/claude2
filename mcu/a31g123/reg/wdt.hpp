#pragma once
// ABOV A31G123 WDT peripheral registers
// Peripheral base: 0x40000000
//
// !! Verify all register offsets and bit definitions against the
//    ABOV A31G123 datasheet before use. !!

#include <cstdint>

struct Wdt_t
{
    struct Cr // 0x00000000 Watch Timer Control Register
    {
        Cr(const uint32_t raw = 0) { r = _WTIDKY | raw; }

        struct Bits
        {
            uint32_t CLKDIV  : 2;
            uint32_t UNFIEN  : 1;
            uint32_t WINMIEN : 1;
            uint32_t CNTEN   : 6;
            uint32_t RSTEN   : 6;
            uint32_t WTIDKY  : 16;
        };

        union
        {
            uint32_t r;
            Bits     b;
        };

        static constexpr uint32_t _CLKDIV0 = (0u << 0);
        static constexpr uint32_t _CLKDIV1 = (1u << 0);
        static constexpr uint32_t _CLKDIV2 = (2u << 0);
        static constexpr uint32_t _CLKDIV3 = (3u << 0);
        static constexpr uint32_t _UNFIEN  = (1u << 2);
        static constexpr uint32_t _WINMIEN = (1u << 3);
        static constexpr uint32_t _CNTEN   = (0u);
        static constexpr uint32_t _CNTDIS  = (0x001A << 4);
        static constexpr uint32_t _RSTEN   = (0u);
        static constexpr uint32_t _RSTDIS  = (0x0025 << 10);
        static constexpr uint32_t _WTIDKY  = (0x5a69 << 16);
    };

    struct Sr                       // 0x00000000 Watch Timer Control Register
    {
        struct Bits
        {
            uint32_t UNFIFLAG  : 1; /*!< [0..0] Watch-Dog Timer Underflow Interrupt Flag */
            uint32_t WINMIFLAG : 1; /*!< [1..1] Watch-Dog Timer Window Match Interrupt Flag */
            uint32_t           : 5;
            uint32_t DBGCNTEN  : 1; /*!< [7..7] Watch-Dog Timer Counter Enable when the core is halted */
        };

        union
        {
            uint32_t r;
            Bits     b;
        };
    };

    volatile Cr       CR;
    volatile Sr       SR;
    volatile uint32_t DR;
    volatile uint32_t CNT;
    volatile uint32_t WINDR;
    volatile uint32_t CNTR;

    void disable() { CR(_RSTDIS | _CNTDIS); }
};

static inline constexpr Wdt_t &WDT(const size_t base) { return *reinterpret_cast<Wdt_t *>(base); }
