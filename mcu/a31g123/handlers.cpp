// A31G123 peripheral interrupt handlers and the MCU-specific vector table extension.
// The linker script places .vectors_a31g123 immediately after .vectors so these
// entries land at vector[16] onward.
//
// All handlers are weak aliases of __stop_a31g123 — override by defining a
// non-weak function with the same name in application or driver code.
//
// IRQ assignments: refer to ABOV A31G123 datasheet, Table "Interrupt Vector".
// Verify with actual datasheet before use.

using ptr_func_t = void (*)();

extern "C" void __stop_a31g123()
{
    while (true)
    {
    }
}

// ── Peripheral IRQ handlers (weak defaults) ─────────────────────────────────
extern "C" __attribute__((weak, alias("__stop_a31g123"))) void LVI_handler();
extern "C" __attribute__((weak, alias("__stop_a31g123"))) void WUT_handler();
extern "C" __attribute__((weak, alias("__stop_a31g123"))) void WDT_handler();
extern "C" __attribute__((weak, alias("__stop_a31g123"))) void EINT0_handler();
extern "C" __attribute__((weak, alias("__stop_a31g123"))) void EINT1_handler();
extern "C" __attribute__((weak, alias("__stop_a31g123"))) void EINT2_handler();
extern "C" __attribute__((weak, alias("__stop_a31g123"))) void EINT3_handler();
extern "C" __attribute__((weak, alias("__stop_a31g123"))) void TIMER10_handler();
extern "C" __attribute__((weak, alias("__stop_a31g123"))) void TIMER11_handler();
extern "C" __attribute__((weak, alias("__stop_a31g123"))) void TIMER12_handler();
extern "C" __attribute__((weak, alias("__stop_a31g123"))) void I2C0_handler();
extern "C" __attribute__((weak, alias("__stop_a31g123"))) void USART10_handler();
extern "C" __attribute__((weak, alias("__stop_a31g123"))) void WT_handler();
extern "C" __attribute__((weak, alias("__stop_a31g123"))) void TIMER30_handler();
extern "C" __attribute__((weak, alias("__stop_a31g123"))) void I2C1_handler();
extern "C" __attribute__((weak, alias("__stop_a31g123"))) void TIMER20_handler();
extern "C" __attribute__((weak, alias("__stop_a31g123"))) void TIMER21_handler();
extern "C" __attribute__((weak, alias("__stop_a31g123"))) void USART11_handler();
extern "C" __attribute__((weak, alias("__stop_a31g123"))) void ADC_handler();
extern "C" __attribute__((weak, alias("__stop_a31g123"))) void UART0_handler();
extern "C" __attribute__((weak, alias("__stop_a31g123"))) void UART1_handler();
extern "C" __attribute__((weak, alias("__stop_a31g123"))) void TIMER13_handler();
extern "C" __attribute__((weak, alias("__stop_a31g123"))) void TIMER14_handler();
extern "C" __attribute__((weak, alias("__stop_a31g123"))) void TIMER15_handler();
extern "C" __attribute__((weak, alias("__stop_a31g123"))) void TIMER16_handler();
extern "C" __attribute__((weak, alias("__stop_a31g123"))) void I2C2_handler();
extern "C" __attribute__((weak, alias("__stop_a31g123"))) void USART12_handler();
extern "C" __attribute__((weak, alias("__stop_a31g123"))) void USART13_handler();

// ── MCU IRQ vector table (vectors 16+) ─────────────────────────────────────
__attribute__((section(".vectors_a31g123"), used)) ptr_func_t __isr_vectors_a31g123[] = {
  LVI_handler,     // 16
  WUT_handler,     // 17
  WDT_handler,     // 18
  EINT0_handler,   // 19
  EINT1_handler,   // 20
  EINT2_handler,   // 21
  EINT3_handler,   // 22
  TIMER10_handler, // 23
  TIMER11_handler, // 24
  TIMER12_handler, // 25
  I2C0_handler,    // 26
  USART10_handler, // 27
  WT_handler,      // 28
  TIMER30_handler, // 29
  I2C1_handler,    // 30
  TIMER20_handler, // 31
  TIMER21_handler, // 32
  USART11_handler, // 33
  ADC_handler,     // 34
  UART0_handler,   // 35
  UART1_handler,   // 36
  TIMER13_handler, // 37
  TIMER14_handler, // 38
  TIMER15_handler, // 39
  TIMER16_handler, // 40
  I2C2_handler,    // 41
  USART12_handler, // 42
  USART13_handler, // 43
};
