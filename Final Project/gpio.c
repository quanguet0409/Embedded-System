#include "gpio.h"

void gpio_init(void)
{
    // Enable clock to ports
    SIM->SCGC5 |= (SIM_SCGC5_PORTC_MASK |
                   SIM_SCGC5_PORTD_MASK |
                   SIM_SCGC5_PORTE_MASK);

    // Configure LED pins
    LED_RED_PORT->PCR[LED_RED_PIN] = PORT_PCR_MUX(1);
    LED_GREEN_PORT->PCR[LED_GREEN_PIN] = PORT_PCR_MUX(1);

    // Configure switch pins with pull-up and interrupt
    SW1_PORT->PCR[SW1_PIN] = PORT_PCR_MUX(1) |
                             PORT_PCR_PE_MASK |
                             PORT_PCR_PS_MASK |
                             PORT_PCR_IRQC(0x0A);

    SW2_PORT->PCR[SW2_PIN] = PORT_PCR_MUX(1) |
                             PORT_PCR_PE_MASK |
                             PORT_PCR_PS_MASK |
                             PORT_PCR_IRQC(0x0A);

    // Set LED pins as outputs
    LED_RED_GPIO->PDDR |= (1 << LED_RED_PIN);
    LED_GREEN_GPIO->PDDR |= (1 << LED_GREEN_PIN);

    // Initial LED state
    gpio_set_pin(LED_RED_GPIO, LED_RED_PIN);     // Turn off (active low)
    gpio_set_pin(LED_GREEN_GPIO, LED_GREEN_PIN); // Turn off (active low)

    // Enable port interrupts
    NVIC_EnableIRQ(PORTC_PORTD_IRQn);
}

void gpio_set_pin(GPIO_Type *gpio, uint8_t pin)
{
    gpio->PSOR = (1 << pin);
}

void gpio_clear_pin(GPIO_Type *gpio, uint8_t pin)
{
    gpio->PCOR = (1 << pin);
}

void gpio_toggle_pin(GPIO_Type *gpio, uint8_t pin)
{
    gpio->PTOR = (1 << pin);
}

uint8_t gpio_read_pin(GPIO_Type *gpio, uint8_t pin)
{
    return (gpio->PDIR & (1 << pin)) ? 1 : 0;
}