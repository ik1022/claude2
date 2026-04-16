// Reset handler and C/C++ runtime initialisation for ARM Cortex-M0.
// Called immediately after the processor releases from reset; runs before
// main_app() so the C/C++ environment is fully set up.

#include <cstdint>

// Linker-script symbols — declared with types that match how they are used
// to avoid -Wcast-align.
extern char     __data_start; // .data destination in SRAM
extern char     __data_end;
extern char     __data_load;  // .data source in Flash (LMA)
extern char     __bss_start;
extern char     __bss_end;
extern uint32_t __heap_start; // used as uint32_t* for heap fill pattern

using init_fn = void (*)();
extern init_fn __preinit_array_start[];
extern init_fn __preinit_array_end[];
extern init_fn __init_array_start[];
extern init_fn __init_array_end[];
extern init_fn __fini_array_start[];
extern init_fn __fini_array_end[];

// Defined in app/main.cpp
extern "C" void main_app();

// ── Memory initialisation ───────────────────────────────────────────────────

static void copy_data()
{
    const char *src = &__data_load;
    char       *dst = &__data_start;
    while (dst < &__data_end)
    {
        *dst++ = *src++;
    }
}

static void zero_bss()
{
    char *p = &__bss_start;
    while (p < &__bss_end)
    {
        *p++ = 0;
    }
}

// Fill the heap with a sentinel pattern so stack-heap collisions can be
// detected during debugging. Reads MSP to find the current stack boundary.
static void fill_heap()
{
    uint32_t msp;
    asm volatile("mrs %0, msp" : "=r"(msp));

    uint32_t *heap  = &__heap_start;
    uint32_t *stack = reinterpret_cast<uint32_t *>(msp);

    while (heap < stack)
    {
        *heap++ = 0x45455246u; // "FREE"
    }
}

// ── C++ static object lifecycle ─────────────────────────────────────────────

static void call_init_array()
{
    for (init_fn *p = __preinit_array_start; p < __preinit_array_end; ++p)
    {
        (*p)();
    }
    for (init_fn *p = __init_array_start; p < __init_array_end; ++p)
    {
        (*p)();
    }
}

static void call_fini_array()
{
    for (init_fn *p = __fini_array_start; p < __fini_array_end; ++p)
    {
        (*p)();
    }
}

// ── Reset entry point ───────────────────────────────────────────────────────
extern "C" void RESET_handler()
{
    copy_data();
    zero_bss();
    fill_heap();
    call_init_array();

    main_app();

    call_fini_array();

    // main_app() should never return; halt if it does.
    while (true)
    {
    }
}
