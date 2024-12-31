#include "switches.h"
#include "step_counter.h"
#include <MKL46Z4.h>

void init_switches(void)
{
    // Enable clock to switch ports
    SIM->SCGC5 |= SIM_SCGC5_PORTC_MASK;

    // Configure switch pins with pull-up and interrupt
    PORTC->PCR[3] = PORT_PCR_MUX(1) | PORT_PCR_PE_MASK | PORT_PCR_PS_MASK | PORT_PCR_IRQC(0x0A);
    PORTC->PCR[12] = PORT_PCR_MUX(1) | PORT_PCR_PE_MASK | PORT_PCR_PS_MASK | PORT_PCR_IRQC(0x0A);

    // Enable interrupts
    NVIC_EnableIRQ(PORTC_PORTD_IRQn);
}

void PORTC_PORTD_IRQHandler(void)
{
    if (PORTC->ISFR & (1 << 3))
    {
        handle_sw1();
        PORTC->ISFR = (1 << 3);
    }
    if (PORTC->ISFR & (1 << 12))
    {
        handle_sw2();
        PORTC->ISFR = (1 << 12);
    }
}

void handle_sw1(void)
{
    toggle_counter();
}

void handle_sw2(void)
{
    reset_counter();
}
