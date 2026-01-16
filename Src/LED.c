/*
 * LED.c
 *
 *  Created on: 7. jan. 2026
 *      Author: Bruger
 */

#include "LED.h"

void led_init() {
	// Set pin PA9 to output, blue
	RCC->AHBENR |= RCC_AHBPeriph_GPIOA; // Enable clock for GPIO Port A
	GPIOA->OSPEEDR &= ~(0x00000003 << (9 * 2)); // Clear speed register
	GPIOA->OSPEEDR |= (0x00000002 << (9 * 2)); // set speed register (0x01 - 10
	// MHz, 0x02 - 2 MHz, 0x03 - 50 MHz)
	GPIOA->OTYPER &= ~(0x0001 << (9)); // Clear output type register
	GPIOA->OTYPER |= (0x0000 << (9)); // Set output type register (0x00 -
	// Push pull, 0x01 - Open drain)
	GPIOA->MODER &= ~(0x00000003 << (9 * 2)); // Clear mode register
	GPIOA->MODER |= (0x00000001 << (9 * 2)); // Set mode register (0x00 –
	// Input, 0x01 - Output, 0x02 - Alternate Function, 0x03 - Analog in/out)

	// Set pin PC7 to output, green
	RCC->AHBENR |= RCC_AHBPeriph_GPIOC; // Enable clock for GPIO Port C
	GPIOC->OSPEEDR &= ~(0x00000003 << (7 * 2)); // Clear speed register
	GPIOC->OSPEEDR |= (0x00000002 << (7 * 2)); // set speed register (0x01 - 10
	// MHz, 0x02 - 2 MHz, 0x03 - 50 MHz)
	GPIOC->OTYPER &= ~(0x0001 << (7)); // Clear output type register
	GPIOC->OTYPER |= (0x0000 << (7)); // Set output type register (0x00 -
	// Push pull, 0x01 - Open drain)
	GPIOC->MODER &= ~(0x00000003 << (7 * 2)); // Clear mode register
	GPIOC->MODER |= (0x00000001 << (7 * 2)); // Set mode register (0x00 –
	// Input, 0x01 - Output, 0x02 - Alternate Function, 0x03 - Analog in/out)

	// Set pin PB4 to output, red
	RCC->AHBENR |= RCC_AHBPeriph_GPIOB; // Enable clock for GPIO Port B
	GPIOB->OSPEEDR &= ~(0x00000003 << (4 * 2)); // Clear speed register
	GPIOB->OSPEEDR |= (0x00000002 << (4 * 2)); // set speed register (0x01 - 10
	// MHz, 0x02 - 2 MHz, 0x03 - 50 MHz)
	GPIOB->OTYPER &= ~(0x0001 << (4)); // Clear output type register
	GPIOB->OTYPER |= (0x0000 << (4)); // Set output type register (0x00 -
	// Push pull, 0x01 - Open drain)
	GPIOB->MODER &= ~(0x00000003 << (4 * 2)); // Clear mode register
	GPIOB->MODER |= (0x00000001 << (4 * 2)); // Set mode register (0x00 –
	// Input, 0x01 - Output, 0x02 - Alternate Function, 0x03 - Analog in/out)
}

void setLED(int blue, int red, int green) {
	GPIOA->ODR |= (0x0001 << 9); //Set pin PA9 (blue) to high
	GPIOB->ODR |= (0x0001 << 4); //Set pin PB4 (red) to high
	GPIOC->ODR |= (0x0001 << 7); //Set pin PC7 (green) to high

	if (blue != 0) {GPIOA->ODR &= ~(0x0001 << 9);} //reset pin PA9 (blue) to low
	if (red != 0) {GPIOB->ODR &= ~(0x0001 << 4);} //reset pin PB4 (red) to low
	if (green != 0) {GPIOC->ODR &= ~(0x0001 << 7);} //reset pin PC7 (green) to low



}
