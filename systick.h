#ifndef __SYSTICK_H
#define __SYSTICK_H

#include <stm32f10x.h>

void SysTick_Init(void);
void SysTick_Handler(void);
uint32_t millis(void);
void hal_delay(uint32_t delay);

#endif
