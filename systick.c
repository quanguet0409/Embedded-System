#include <stm32f10x.h>
#include "systick.h"

uint32_t usTick = 0;
uint32_t msTick = 0;

void SysTick_Init(void) {
		SysTick->LOAD |= SystemCoreClock / 1000 - 1;
		SysTick->CTRL |= SysTick_CTRL_CLKSOURCE | SysTick_CTRL_TICKINT;
		SysTick->CTRL |= SysTick_CTRL_ENABLE;
		NVIC_SetPriority(SysTick_IRQn, 1); 
		NVIC_EnableIRQ(SysTick_IRQn);
}

void hal_IncTick(void) {
	msTick += 1;
}

uint32_t hal_GetTick(void) {
		return msTick;
}

void SysTick_Handler(void) {
		SysTick->CTRL |= SysTick_CTRL_COUNTFLAG; //  manually force the SysTick timer to indicate that it has counted to zero, even if it hasn't actually reached zero
		hal_IncTick(); // Increase tick
}

uint32_t millis(void) {
		return msTick;
}

void hal_delay(uint32_t delay) {
		uint32_t tickstart = hal_GetTick();
		
		while (hal_GetTick - tickstart < delay) {}
}
