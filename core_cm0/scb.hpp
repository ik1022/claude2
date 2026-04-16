#pragma once
// ARM Cortex-M0 System Control Block
// Base address: 0xE000ED00  (ARM DDI0432C)

#include <cstdint>

struct Scb
{
    volatile uint32_t CPUID; // 0x00  CPUID Base Register (RO)
    volatile uint32_t ICSR;  // 0x04  Interrupt Control and State Register
    uint32_t          _0;    // 0x08  VTOR — not present on CM0
    volatile uint32_t AIRCR; // 0x0C  Application Interrupt and Reset Control
    volatile uint32_t SCR;   // 0x10  System Control Register
    volatile uint32_t CCR;   // 0x14  Configuration and Control Register
    uint32_t          _1;    // 0x18  SHPR1 — not present on CM0
    volatile uint32_t SHPR2; // 0x1C  System Handler Priority Register 2
    volatile uint32_t SHPR3; // 0x20  System Handler Priority Register 3

    // Trigger a software system reset.
    void system_reset()
    {
        AIRCR = (0x05FAu << 16) | (1u << 2);
        while (true)
        {
        }
    }

    // Enable/disable sleep-on-exit (return from ISR enters WFI).
    void sleep_on_exit(bool enable)
    {
        if (enable)
        {
            SCR |= (1u << 1);
        }
        else
        {
            SCR &= ~(1u << 1);
        }
    }
};

inline Scb &SCB = *reinterpret_cast<Scb *>(0xE000ED00u);
