#include "pedometer.h"
#include <MKL46Z4.h>
#include <stdio.h>

// Global variables
volatile uint32_t step_count = 0;
volatile uint8_t is_active = 0;

void init_hardware(void)
{
    // Initialize accelerometer, LEDs, switches, and LCD
    init_accelerometer();
    init_leds();
    init_switches();
    init_lcd();
}

void main(void)
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
