/*
 * LED.h
 *
 *  Created on: 7. jan. 2026
 *      Author: Kristine
 */

#ifndef LED_H_
#define LED_H_

#include "stm32f30x_conf.h" // STM32 config
#include "30010_io.h" // Input/output library for this course

void led_init();
void setLED(int blue, int red, int green);

#endif /* LED_H_ */
