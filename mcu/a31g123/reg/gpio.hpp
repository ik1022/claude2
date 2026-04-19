#pragma once
// ABOV A31G123 GPIO peripheral registers
// Peripheral base: 0x40000000
//
// !! Verify all register offsets and bit definitions against the
//    ABOV A31G123 datasheet before use. !!

#include <cstdint>

struct GpioPort
{
    volatile uint32_t MOD;   // 0x00  Port Mode Register (2 bits/pin: 00=Input 01=Push-Pull 10=Open-Drain 11=Input)
    volatile uint32_t TYP;   // 0x04  Output Type Register
    volatile uint32_t AFSR0; // 0x08  Alternate Function Select Register 0 (pins 0-7)
    volatile uint32_t AFSR1; // 0x0C  Alternate Function Select Register 1 (pins 8-15)
    volatile uint32_t PUPD;  // 0x10  Pull-Up/Down Register (2 bits/pin: 00=Floating 01=Pull-Up 10=Pull-Down)
    volatile uint32_t INDR;  // 0x14  Input Data Register
    volatile uint32_t OUTR;  // 0x18  Output Data Register
    volatile uint32_t BSR;   // 0x1C  Bit Set Register (write 1 to set)
    volatile uint32_t BCR;   // 0x20  Bit Clear Register (write 1 to clear)
    volatile uint32_t OMSR;  // 0x24  Output Mode Set Register
    volatile uint32_t DBCR;  // 0x28  Debounce Control Register
};

// GPIO base addresses — verify with A31G123 datasheet memory map
inline GpioPort &PA = *reinterpret_cast<GpioPort *>(0x30000000u);
inline GpioPort &PB = *reinterpret_cast<GpioPort *>(0x30000100u);
inline GpioPort &PC = *reinterpret_cast<GpioPort *>(0x30000200u);
inline GpioPort &PD = *reinterpret_cast<GpioPort *>(0x30000300u);
inline GpioPort &PE = *reinterpret_cast<GpioPort *>(0x30000400u);
inline GpioPort &PF = *reinterpret_cast<GpioPort *>(0x30000500u);

// Helper: return GpioPort reference from port index 0=PA .. 5=PF
inline GpioPort &gpio_port(uint32_t idx) { return *reinterpret_cast<GpioPort *>(0x30000000u + idx * 0x100u); }
