#include "switches.h"
#include "gpio.h"
#include "step_counter.h"

void init_switches(void)
{
    // Switches are initialized in gpio_init()
}

void PORTC_PORTD_IRQHandler(void)
{
    // Check which switch caused the interrupt
    if (PORTC->ISFR & (1 << SW1_PIN))
    {
        toggle_counter();
        PORTC->ISFR = (1 << SW1_PIN); // Clear interrupt flag
    }

    if (PORTC->ISFR & (1 << SW2_PIN))
    {
        reset_counter();
        PORTC->ISFR = (1 << SW2_PIN); // Clear interrupt flag
    }
}