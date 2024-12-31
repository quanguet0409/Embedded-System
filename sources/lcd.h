#ifndef LCD_H
#define LCD_H

#include <stdint.h>

void init_lcd(void);
void display_steps(uint32_t steps);

#endif

// lcd.c
#include "lcd.h"
#include <MKL46Z4.h>

void init_lcd(void)
{
    // Enable clock to LCD ports
    SIM->SCGC5 |= SIM_SCGC5_PORTD_MASK;

    // Configure LCD pins as GPIO
    PORTD->PCR[0] = PORT_PCR_MUX(1); // RS
    PORTD->PCR[1] = PORT_PCR_MUX(1); // EN
    PORTD->PCR[2] = PORT_PCR_MUX(1); // D4
    PORTD->PCR[3] = PORT_PCR_MUX(1); // D5
    PORTD->PCR[4] = PORT_PCR_MUX(1); // D6
    PORTD->PCR[5] = PORT_PCR_MUX(1); // D7

    // Set pins as outputs
    GPIOD->PDDR |= (1 << 0) | (1 << 1) | (1 << 2) | (1 << 3) | (1 << 4) | (1 << 5);

    // Initialize LCD in 4-bit mode
    // Add your LCD initialization sequence here
}

void display_steps(uint32_t steps)
{
    char buffer[16];
    sprintf(buffer, "Steps: %lu", steps);

    // Clear display first
    // Write buffer to LCD
    // Add your LCD writing sequence here
}
