#include "systick.h"
#include "leds.h"
#include <MKL46Z4.h>

volatile uint32_t systick_counter = 0;
volatile uint32_t led_counter = 0;

void init_systick(void)
{
    // Configure SysTick for 1ms intervals
    SysTick->LOAD = SystemCoreClock / 1000 - 1;
    SysTick->VAL = 0;
    SysTick->CTRL = SysTick_CTRL_CLKSOURCE_Msk |
                    SysTick_CTRL_TICKINT_Msk |
                    SysTick_CTRL_ENABLE_Msk;
}

void delay_ms(uint32_t ms)
{
    systick_counter = ms;
    while (systick_counter > 0)
        ;
}

void SysTick_Handler(void)
{
    if (systick_counter > 0)
    {
        systick_counter--;
    }

    // Handle LED blinking
    led_counter++;
    if (led_counter >= 500)
    { // Toggle every 500ms for 1Hz blink
        led_counter = 0;
        if (is_active)
        {
            toggle_green_led();
        }
    }
}