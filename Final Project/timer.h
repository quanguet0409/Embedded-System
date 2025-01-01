#ifndef TIMER_H
#define TIMER_H

#include <stdint.h>

void timer_init(void);
void timer_start(void);
void timer_stop(void);
void delay_ms(uint32_t ms);

#endif