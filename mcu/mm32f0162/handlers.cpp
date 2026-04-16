// MM32F0162 peripheral interrupt handlers and the MCU-specific vector table extension.
// The linker script places .vectors_mm32f0162 immediately after .vectors so these
// entries land at vector[16] onward.
//
// IRQ assignments: refer to MindMotion MM32F0162 datasheet, Table "Vector Table".
// Verify with actual datasheet before use.

using ptr_func_t = void (*)();

extern "C" void __stop_mm32f0162()
{
    while (true)
    {
    }
}

extern "C" void DUMMY_handler();

// ── Peripheral IRQ handlers (weak defaults) ─────────────────────────────────
extern "C" __attribute__((weak, alias("__stop_mm32f0162"))) void WWDG_handler();
extern "C" __attribute__((weak, alias("__stop_mm32f0162"))) void PVD_handler();
extern "C" __attribute__((weak, alias("__stop_mm32f0162"))) void RTC_handler();
extern "C" __attribute__((weak, alias("__stop_mm32f0162"))) void FLASH_handler();
extern "C" __attribute__((weak, alias("__stop_mm32f0162"))) void RCC_handler();
extern "C" __attribute__((weak, alias("__stop_mm32f0162"))) void EXTI0_1_handler();
extern "C" __attribute__((weak, alias("__stop_mm32f0162"))) void EXTI2_3_handler();
extern "C" __attribute__((weak, alias("__stop_mm32f0162"))) void EXTI4_15_handler();
extern "C" __attribute__((weak, alias("__stop_mm32f0162"))) void DMA1_Ch1_handler();
extern "C" __attribute__((weak, alias("__stop_mm32f0162"))) void DMA1_Ch2_3_handler();
extern "C" __attribute__((weak, alias("__stop_mm32f0162"))) void DMA1_Ch4_5_handler();
extern "C" __attribute__((weak, alias("__stop_mm32f0162"))) void ADC_handler();
extern "C" __attribute__((weak, alias("__stop_mm32f0162"))) void TIM1_BRK_UP_TRG_COM_handler();
extern "C" __attribute__((weak, alias("__stop_mm32f0162"))) void TIM1_CC_handler();
extern "C" __attribute__((weak, alias("__stop_mm32f0162"))) void TIM3_handler();
extern "C" __attribute__((weak, alias("__stop_mm32f0162"))) void TIM14_handler();
extern "C" __attribute__((weak, alias("__stop_mm32f0162"))) void TIM16_handler();
extern "C" __attribute__((weak, alias("__stop_mm32f0162"))) void TIM17_handler();
extern "C" __attribute__((weak, alias("__stop_mm32f0162"))) void I2C1_handler();
extern "C" __attribute__((weak, alias("__stop_mm32f0162"))) void SPI1_handler();
extern "C" __attribute__((weak, alias("__stop_mm32f0162"))) void USART1_handler();
extern "C" __attribute__((weak, alias("__stop_mm32f0162"))) void USART2_handler();

// ── MCU IRQ vector table (vectors 16+) ─────────────────────────────────────
__attribute__((section(".vectors_mm32f0162"), used)) ptr_func_t __isr_vectors_mm32f0162[] = {
  WWDG_handler,                // 16
  PVD_handler,                 // 17
  RTC_handler,                 // 18
  FLASH_handler,               // 19
  RCC_handler,                 // 20
  EXTI0_1_handler,             // 21
  EXTI2_3_handler,             // 22
  EXTI4_15_handler,            // 23
  DUMMY_handler,               // 24  Reserved
  DMA1_Ch1_handler,            // 25
  DMA1_Ch2_3_handler,          // 26
  DMA1_Ch4_5_handler,          // 27
  ADC_handler,                 // 28
  TIM1_BRK_UP_TRG_COM_handler, // 29
  TIM1_CC_handler,             // 30
  DUMMY_handler,               // 31  Reserved
  TIM3_handler,                // 32
  DUMMY_handler,               // 33  Reserved
  DUMMY_handler,               // 34  Reserved
  TIM14_handler,               // 35
  DUMMY_handler,               // 36  Reserved
  TIM16_handler,               // 37
  TIM17_handler,               // 38
  I2C1_handler,                // 39
  DUMMY_handler,               // 40  Reserved
  SPI1_handler,                // 41
  DUMMY_handler,               // 42  Reserved
  USART1_handler,              // 43
  USART2_handler,              // 44
};
