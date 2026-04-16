// Initial stack pointer value placed at the very first word of the vector table.
// The linker script places the .stack section before .vectors so the processor
// reads this value as the initial SP on reset.

extern char __stacktop; // defined by linker script (top of SRAM)

__attribute__((section(".stack"), used)) void *__stack_init = &__stacktop;
