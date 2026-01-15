/*
 * ADC.h
 *
 *  Created on: 13. jan. 2026
 *      Author: Bruger
 */

#ifndef ADC_H_
#define ADC_H_
#include "defs.h"

typedef struct {
int32_t c1, c2;
} ADC_t;

void ADC_init();
void ADC_config(uint8_t channel);
void ADC_measure (ADC_t *adc);
uint8_t button();

#endif /* ADC_H_ */
