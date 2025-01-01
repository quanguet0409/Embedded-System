#include "systick.h"
#include <MKL46Z4.h>

volatile uint32_t systick_counter = 0;

void init_systick(void)
{
    // Configure SysTick for 1ms interrupts
    SysTick->LOAD = (SystemCoreClock / 1000) - 1;
    SysTick->VAL = 0;
    SysTick->CTRL = SysTick_CTRL_CLKSOURCE_Msk |
                    SysTick_CTRL_TICKINT_Msk |
                    SysTick_CTRL_ENABLE_Msk;
}

void SysTick_Handler(void)
{
    systick_counter++;
}

void delay_ms(uint32_t ms)
{
    uint32_t start = systick_counter;
    while ((systick_counter - start) < ms)
        ;
}