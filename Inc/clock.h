/*
 * clock.h
 *
 *  Created on: 8. jan. 2026
 *      Author: Bruger
 */

#ifndef CLOCK_H_
#define CLOCK_H_
#include "defs.h"

typedef struct {
int32_t h, m, s, cs;
} times_t;

times_t t;

void clock_init();
void TIM1_BRK_TIM15_IRQHandler();
void interrupt_update();

#endif /* CLOCK_H_ */
