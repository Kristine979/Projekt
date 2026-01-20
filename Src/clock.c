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
		if (t.s < 59) {t.s += 1; t.five_sec_counter +=1;}
		else {
			t.s = 0;
			t.m += 1;
		}
	}
	t.bullet_speed_counter += 1;
	t.astroid_clock += 1;
	if (t.astroid_clock == 5) {t.astroid_clock = 0; t.astroid_flag += 1;}
	if (t.bullet_speed_counter == 5) {t.bullet_speed_counter = 0; t.bullet_flag += 1;}
	if (t.cs == 1 && (t.s == 30 || t.s == 59)) t.pu_flag = 1;
	if (t.cs == 1) {t.counter_flag = 1; t.alien_led_clock+=1;}
	if (t.cs == 1 ||t.cs == 10 || t.cs == 20 || t.cs == 30 || t.cs == 40
			||t.cs == 50 || t.cs == 60 || t.cs == 70 || t.cs == 80 || t.cs == 90) {t.ship_clock += 1;}
	TIM15->SR &= ~0x0001; // Clear interrupt bit
}
