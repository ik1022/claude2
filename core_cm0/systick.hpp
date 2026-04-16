#pragma once
// ARM Cortex-M0 SysTick timer
// Base address: 0xE000E010  (ARM DDI0432C)

#include <cstdint>

struct SysTick_t
{
    struct Csr
    {
        volatile uint32_t         r;
        static constexpr uint32_t ENABLE    = (1u << 0);
        static constexpr uint32_t TICKINT   = (1u << 1);
        static constexpr uint32_t CLKSOURCE = (1u << 2); // 1 = processor clock
        static constexpr uint32_t COUNTFLAG = (1u << 16);
    } CSR;

    volatile uint32_t RVR;                               // 0x04  Reload Value Register (24-bit)
    volatile uint32_t CVR;                               // 0x08  Current Value Register (write any to clear)
    volatile uint32_t CALIB;                             // 0x0C  Calibration register (read-only)

    // Configure and start the timer.
    // interval_ticks: number of processor clock cycles per interrupt.
    void start(uint32_t interval_ticks)
    {
        RVR   = (interval_ticks - 1u) & 0x00FFFFFFu;
        CVR   = 0;
        CSR.r = Csr::ENABLE | Csr::TICKINT | Csr::CLKSOURCE;
    }

    void stop() { CSR.r = 0; }
};

inline SysTick_t &SYSTICK = *reinterpret_cast<SysTick_t *>(0xE000E010u);
