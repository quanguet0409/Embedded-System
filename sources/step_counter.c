#include "step_counter.h"
#include "mma8451.h"
#include "leds.h"
#include "lcd.h"
#include "switches.h"
#include "systick.h"
#include <MKL46Z4.h>

volatile uint32_t step_count = 0;
volatile uint8_t is_active = 0;

void init_hardware(void)
{
    // Initialize all peripherals
    init_systick();
    init_accelerometer();
    init_leds();
    init_switches();
    init_lcd();

    // Initial display
    display_steps(0);
    update_leds(0);
}

int main(void)
{
    init_hardware();

    while (1)
    {
        if (is_active)
        {
            if (detect_step())
            {
                step_count++;
                display_steps(step_count);
            }
        }
    }
}

void toggle_counter(void)
{
    is_active = !is_active;
    update_leds(is_active);
}

void reset_counter(void)
{
    step_count = 0;
    display_steps(step_count);
}