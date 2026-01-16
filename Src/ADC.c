/*
 * ADC.c
 *
 *  Created on: 13. jan. 2026
 *      Author: Bruger
 */


#include "ADC.h"

void ADC_init() {
	// initialize joystick
	RCC->AHBENR |= RCC_AHBPeriph_GPIOA; // Enable clock for GPIO Port A

	// Set pin PA6 to input (joystick)
	GPIOA->MODER &= ~(0x00000003 << (6 * 2)); // Clear mode register
	GPIOA->MODER |= (0x00000000 << (6 * 2)); // Set mode register (0x00 –
	// Input, 0x01 - Output, 0x02 - Alternate Function, 0x03 - Analog in/out)
	GPIOA->PUPDR &= ~(0x00000003 << (6 * 2)); // Clear push/pull register
	GPIOA->PUPDR |= (0x00000002 << (6 * 2)); // Set push/pull register (0x00 -
	// No pull, 0x01 - Pull-up, 0x02 - Pull-down)

	// Set pin PA7 to input (joystick)
	GPIOA->MODER &= ~(0x00000003 << (7 * 2)); // Clear mode register
	GPIOA->MODER |= (0x00000000 << (7 * 2)); // Set mode register (0x00 –
	// Input, 0x01 - Output, 0x02 - Alternate Function, 0x03 - Analog in/out)
	GPIOA->PUPDR &= ~(0x00000003 << (7 * 2)); // Clear push/pull register
	GPIOA->PUPDR |= (0x00000002 << (7 * 2)); // Set push/pull register (0x00 -
	// No pull, 0x01 - Pull-up, 0x02 - Pull-down)

	//initialize buttons
	RCC->AHBENR |= RCC_AHBPeriph_GPIOB; // Enable clock for GPIO Port B
	// Set pin PB0 to input (B2 on joystick)
	GPIOB->MODER &= ~(0x00000003 << (0 * 2)); // Clear mode register
	GPIOB->MODER |= (0x00000000 << (0 * 2)); // Set mode register (0x00 –
	// Input, 0x01 - Output, 0x02 - Alternate Function, 0x03 - Analog in/out)
	GPIOB->PUPDR &= ~(0x00000003 << (0 * 2)); // Clear push/pull register
	GPIOB->PUPDR |= (0x00000002 << (0 * 2)); // Set push/pull register (0x00 -
	// No pull, 0x01 - Pull-up, 0x02 - Pull-down)

	// Set pin PA4 to input (B1 on joystick)
	GPIOA->MODER &= ~(0x00000003 << (4 * 2)); // Clear mode register
	GPIOA->MODER |= (0x00000000 << (4 * 2)); // Set mode register (0x00 –
	// Input, 0x01 - Output, 0x02 - Alternate Function, 0x03 - Analog in/out)
	GPIOA->PUPDR &= ~(0x00000003 << (4 * 2)); // Clear push/pull register
	GPIOA->PUPDR |= (0x00000002 << (4 * 2)); // Set push/pull register (0x00 -
	// No pull, 0x01 - Pull-up, 0x02 - Pull-down)

	// setup of ADC

	RCC->CFGR2 &= ~RCC_CFGR2_ADCPRE12; // Clear ADC12 prescaler bits
	RCC->CFGR2 |= RCC_CFGR2_ADCPRE12_DIV6; // Set ADC12 prescaler to 6
	RCC->AHBENR |= RCC_AHBPeriph_ADC12; // Enable clock for ADC12

	ADC1->CR = 0x00000000; // Clear CR register
	ADC1->CFGR &= 0xFDFFC007; // Clear ADC1 config register
	ADC1->SQR1 &= ~ADC_SQR1_L; // Clear regular sequence register 1

	ADC1->CR |= 0x10000000; // Enable internal ADC voltage regulator
	for (int i = 0 ; i < 1000 ; i++) {} // Wait for about 16 microseconds

	ADC1->CR |= 0x80000000; // Start ADC1 calibration
	while (!(ADC1->CR & 0x80000000)); // Wait for calibration to finish
	for (int i = 0 ; i < 100 ; i++) {} // Wait for a little while

	ADC1->CR |= 0x00000001; // Enable ADC1 (0x01 - Enable, 0x02 - Disable)
	while (!(ADC1->ISR & 0x00000001)); // Wait until ready
}

void ADC_config(uint8_t channel) { // ADC_Channel_1 or ADC_Channel_2
	ADC_RegularChannelConfig(ADC1, channel, 1, ADC_SampleTime_1Cycles5);
}

void ADC_measure(ADC_t *adc) {
	// ADC1
	ADC_config(ADC_Channel_15);
	ADC_StartConversion(ADC1); // Start ADC read
	while (ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC) == 0); // Wait for ADC read
	adc->c1 = ADC_GetConversionValue(ADC1); // Read the ADC value

	// ADC2
	ADC_config(ADC_Channel_10);
	ADC_StartConversion(ADC1); // Start ADC read
	while (ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC) == 0); // Wait for ADC read
	adc->c2 = ADC_GetConversionValue(ADC1); // Read the ADC value
}

uint8_t button() {
	uint8_t output = 0;
		uint16_t val;
		val = GPIOB->IDR & (0x0001 << 0); //Read from pin PB0 (B2)
		if (val != 0) { output = 1;}
		val = 0;

		val = GPIOA->IDR & (0x0001 << 4); //Read from pin PA4 (B1)
		if (val != 0) {output = 2;}
		val = 0;
		return output;
}


