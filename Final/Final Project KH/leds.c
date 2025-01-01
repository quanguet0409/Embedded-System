#include "leds.h"
#include <MKL46Z4.h>

void init_leds(void)
{
    // Enable clock to LED ports
    SIM->SCGC5 |= SIM_SCGC5_PORTD_MASK | SIM_SCGC5_PORTE_MASK;

    // Configure LED pins
    PORTD->PCR[5] = PORT_PCR_MUX(1);  // Green LED
    PORTE->PCR[29] = PORT_PCR_MUX(1); // Red LED

    // Set pins as outputs
    GPIOD->PDDR |= (1 << 5);
    GPIOE->PDDR |= (1 << 29);

    // Turn off both LEDs initially
    GPIOD->PSOR = (1 << 5);
    GPIOE->PSOR = (1 << 29);
}

void update_leds(uint8_t active)
{
    if (active)
    {
        // Turn on green LED, turn off red LED
        GPIOD->PCOR = (1 << 5);  // Green LED on
        GPIOE->PSOR = (1 << 29); // Red LED off
    }
    else
    {
        // Turn on red LED, turn off green LED
        GPIOD->PSOR = (1 << 5);  // Green LED off
        GPIOE->PCOR = (1 << 29); // Red LED on
    }
}

void toggle_green_led(void)
{
    GPIOD->PTOR = (1 << 5);
}