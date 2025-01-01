#include "timer.h"
#include "leds.h"
#include <MKL46Z4.h>

#define TIMER_FREQ 48000000 // 48MHz clock
#define MS_PRESCALER 48000  // For 1ms timing

volatile uint32_t ms_counter = 0;
extern volatile uint8_t is_active;

void timer_init(void)
{
    // Enable clock to TPM0
    SIM->SCGC6 |= SIM_SCGC6_TPM0_MASK;

    // Select MCGFLLCLK clock source
    SIM->SOPT2 |= SIM_SOPT2_TPMSRC(1);

    // Configure TPM0 for 1ms interrupts
    TPM0->MOD = MS_PRESCALER - 1;
    TPM0->SC = TPM_SC_PS(0) |    // Prescaler = 1
               TPM_SC_TOIE_MASK; // Enable overflow interrupt

    // Enable TPM0 interrupt
    NVIC_EnableIRQ(TPM0_IRQn);
}

void timer_start(void)
{
    TPM0->SC |= TPM_SC_CMOD(1); // Start timer
}

void timer_stop(void)
{
    TPM0->SC &= ~TPM_SC_CMOD_MASK; // Stop timer
}

void delay_ms(uint32_t ms)
{
    ms_counter = ms;
    while (ms_counter > 0)
        ;
}

void TPM0_IRQHandler(void)
{
    static uint32_t led_counter = 0;

    // Clear overflow flag
    TPM0->SC |= TPM_SC_TOF_MASK;

    if (ms_counter > 0)
    {
        ms_counter--;
    }

    // Handle LED blinking when active
    if (is_active)
    {
        led_counter++;
        if (led_counter >= 500)
        { // Toggle every 500ms (1Hz)
            led_counter = 0;
            toggle_green_led();
        }
    }
}