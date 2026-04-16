#pragma once
// ARM Cortex-M0 NVIC — Nested Vectored Interrupt Controller
// Base address: 0xE000E100  (ARM DDI0432C)

#include <cstdint>

struct Nvic
{
    volatile uint32_t ISER[1]; // 0x000  Interrupt Set-Enable
    uint32_t          _0[31];
    volatile uint32_t ICER[1]; // 0x080  Interrupt Clear-Enable
    uint32_t          _1[31];
    volatile uint32_t ISPR[1]; // 0x100  Interrupt Set-Pending
    uint32_t          _2[31];
    volatile uint32_t ICPR[1]; // 0x180  Interrupt Clear-Pending
    uint32_t          _3[95];
    volatile uint32_t IPR[8];  // 0x300  Interrupt Priority (2 bits per IRQ on CM0)

    // Enable/disable individual IRQs (irq = 0..31)
    void enable(uint32_t irq) { ISER[0] = (1u << irq); }

    void disable(uint32_t irq) { ICER[0] = (1u << irq); }

    // Set/clear pending state
    void set_pending(uint32_t irq) { ISPR[0] = (1u << irq); }

    void clear_pending(uint32_t irq) { ICPR[0] = (1u << irq); }

    // Set priority (priority: 0=highest, 3=lowest on CM0; stored in bits[7:6])
    void set_priority(uint32_t irq, uint32_t priority)
    {
        uint32_t shift = (irq & 3u) * 8u + 6u;
        uint32_t idx   = irq >> 2u;
        IPR[idx]       = (IPR[idx] & ~(0x3u << shift)) | ((priority & 0x3u) << shift);
    }

    static void global_enable() { asm volatile("cpsie i" ::: "memory"); }

    static void global_disable() { asm volatile("cpsid i" ::: "memory"); }
};

inline Nvic &NVIC = *reinterpret_cast<Nvic *>(0xE000E100u);
