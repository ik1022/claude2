/* MindMotion MM32F0162 linker script
 * Flash: 64 KB @ 0x08000000
 * SRAM:   8 KB @ 0x20000000
 *
 * Verify memory sizes against the actual datasheet / device variant.
 */

MEMORY
{
    FLASH (rx)  : ORIGIN = 0x08000000, LENGTH = 64K
    SRAM  (rwx) : ORIGIN = 0x20000000, LENGTH = 8K
}

_stack_size = 0x400;   /* 1 KB stack — adjust as needed */

ENTRY(RESET_handler)

SECTIONS
{
    /* ── Vector table ──────────────────────────────────────────────────────
     * Word 0   : initial SP              (.stack from core_cm0/stack.cpp)
     * Words 1-15 : CM0 exceptions        (.vectors from core_cm0/handlers.cpp)
     * Words 16+ : MM32F0162 IRQs         (.vectors_mm32f0162 from mcu/mm32f0162/handlers.cpp)
     */
    .vectors :
    {
        KEEP(*(.stack))
        KEEP(*(.vectors))
        KEEP(*(.vectors_mm32f0162))
    } > FLASH

    /* ── Code and read-only data ───────────────────────────────────────── */
    .text :
    {
        *(.text*)
        *(.rodata*)
        . = ALIGN(4);
    } > FLASH

    .preinit_array :
    {
        __preinit_array_start = .;
        KEEP(*(.preinit_array))
        __preinit_array_end = .;
    } > FLASH

    .init_array :
    {
        __init_array_start = .;
        KEEP(*(SORT(.init_array.*)))
        KEEP(*(.init_array))
        __init_array_end = .;
    } > FLASH

    .fini_array :
    {
        __fini_array_start = .;
        KEEP(*(SORT(.fini_array.*)))
        KEEP(*(.fini_array))
        __fini_array_end = .;
    } > FLASH

    /* ── Initialised data (copied Flash→SRAM on startup) ───────────────── */
    __data_load = LOADADDR(.data);

    .data :
    {
        __data_start = .;
        *(.data*)
        . = ALIGN(4);
        __data_end = .;
    } > SRAM AT > FLASH

    /* ── Zero-initialised data ─────────────────────────────────────────── */
    .bss (NOLOAD) :
    {
        __bss_start = .;
        *(.bss*)
        *(COMMON)
        . = ALIGN(4);
        __bss_end = .;
    } > SRAM

    /* ── Heap ──────────────────────────────────────────────────────────── */
    .heap (NOLOAD) :
    {
        . = ALIGN(8);
        __heap_start = .;
    } > SRAM

    /* ── Stack (top of SRAM) ───────────────────────────────────────────── */
    .stack (NOLOAD) :
    {
        . = ORIGIN(SRAM) + LENGTH(SRAM) - _stack_size;
        . = ALIGN(8);
        __stackbase = .;
        . += _stack_size;
        __stacktop  = .;
    } > SRAM

    /DISCARD/ :
    {
        *(.ARM.exidx*)
        *(.gnu.linkonce.armexidx.*)
    }
}
