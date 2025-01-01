#ifndef LEDS_H
#define LEDS_H

#include <stdint.h>

void init_leds(void);
void update_leds(uint8_t active);
void toggle_green_led(void);

#endif