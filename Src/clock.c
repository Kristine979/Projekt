/*
 * clock.c
 *
 *  Created on: 8. jan. 2026
 *      Author: Bruger
 */

#include "clock.h"

void clock_init() {
	RCC->APB2ENR = RCC_APB2Periph_TIM15; // Enable clock line to timer 15;
	TIM15->CR1 = 0x00000000; // Configure timer 15, counter disabled
	TIM15->ARR = 0x1900; // Set reload value, 100Hz (6400)
	TIM15->PSC = 0x63; // Set prescale value, (99)
	TIM15->CR1 = 0x00000001; // Configure timer 15, counter enabled
	TIM15->DIER |= 0x0001; // Enable timer 15 interrupts
	NVIC_SetPriority(TIM1_BRK_TIM15_IRQn, 1); // Set interrupt priority
	NVIC_EnableIRQ(TIM1_BRK_TIM15_IRQn); // Enable interrupt
}

times_t t = {0};

void TIM1_BRK_TIM15_IRQHandler() {
	if (t.cs < 99) {t.cs += 1;}
	else {
		t.cs = 0;
		if (t.s < 59) {t.s += 1;}
		else {
			t.s = 0;
			if (t.m < 59) {t.m += 1;}
			else {
				t.m = 0;
			}
		}
	}
	TIM15->SR &= ~0x0001; // Clear interrupt bit
}
