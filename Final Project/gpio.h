#ifndef GPIO_H
#define GPIO_H

#include <MKL46Z4.h>
#include <stdint.h>

// GPIO Pin definitions
#define LED_RED_PIN 29
#define LED_GREEN_PIN 5
#define SW1_PIN 3
#define SW2_PIN 12

// GPIO Port definitions
#define LED_RED_PORT PORTE
#define LED_GREEN_PORT PORTD
#define SW1_PORT PORTC
#define SW2_PORT PORTC

// GPIO definitions
#define LED_RED_GPIO GPIOE
#define LED_GREEN_GPIO GPIOD
#define SW1_GPIO GPIOC
#define SW2_GPIO GPIOC

void gpio_init(void);
void gpio_set_pin(GPIO_Type *gpio, uint8_t pin);
void gpio_clear_pin(GPIO_Type *gpio, uint8_t pin);
void gpio_toggle_pin(GPIO_Type *gpio, uint8_t pin);
uint8_t gpio_read_pin(GPIO_Type *gpio, uint8_t pin);

#endif