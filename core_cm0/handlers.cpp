// ARM Cortex-M0 core exception handlers and the first half of the vector table.
//
// Vector table memory layout (see ARM DDI0419):
//   Word 0  : initial SP           ← from core_cm0/stack.cpp  (.stack section)
//   Word 1  : Reset                ┐
//   Word 2  : NMI                  │
//   Word 3  : HardFault            │
//   Words 4-10 : Reserved (0)      │ this file  (.vectors section)
//   Word 11 : SVCall               │
//   Words 12-13 : Reserved (0)     │
//   Word 14 : PendSV               │
//   Word 15 : SysTick              ┘
//   Words 16+ : MCU IRQs           ← from mcu/<mcu>/handlers.cpp  (.vectors_<mcu>)

using ptr_func_t = void (*)();

// Default handler: spin forever. All weak aliases point here until overridden.
extern "C" void __stop()
{
    while (true)
    {
    }
}

// ── Core exception handlers (weak — override in application) ────────────────
extern "C" __attribute__((weak, alias("__stop"))) void RESET_handler();
extern "C" __attribute__((weak, alias("__stop"))) void NMI_handler();
extern "C" __attribute__((weak, alias("__stop"))) void HARDFAULT_handler();
extern "C" __attribute__((weak, alias("__stop"))) void SVC_handler();
extern "C" __attribute__((weak, alias("__stop"))) void PENDSV_handler();
extern "C" __attribute__((weak, alias("__stop"))) void SYSTICK_handler();
extern "C" __attribute__((weak, alias("__stop"))) void DUMMY_handler();

// ── Core vector table ───────────────────────────────────────────────────────
// Placed in .vectors; the linker script concatenates .stack before this,
// so RESET_handler lands at vector[1] (offset 0x04) as required.
__attribute__((section(".vectors"), used)) ptr_func_t __isr_vectors[] = {
  RESET_handler,     // 1  Reset
  NMI_handler,       // 2  NMI
  HARDFAULT_handler, // 3  HardFault
  DUMMY_handler,     // 4  Reserved
  DUMMY_handler,     // 5  Reserved
  DUMMY_handler,     // 6  Reserved
  DUMMY_handler,     // 7  Reserved
  DUMMY_handler,     // 8  Reserved
  DUMMY_handler,     // 9  Reserved
  DUMMY_handler,     // 10 Reserved
  SVC_handler,       // 11 SVCall
  DUMMY_handler,     // 12 Reserved
  DUMMY_handler,     // 13 Reserved
  PENDSV_handler,    // 14 PendSV
  SYSTICK_handler,   // 15 SysTick
};
