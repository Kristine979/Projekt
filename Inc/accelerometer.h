/*
 * accelerometer.h
 *
 *  Created on: 15. jan. 2026
 *      Author: Caroline
 */

#ifndef ACCELEROMETER_H_
#define ACCELEROMETER_H_

#include "stm32f30x.h"
#include "stm32f30x_rcc.h"
#include "stm32f30x_gpio.h"
#include <stdint.h>
#include "defs.h"

void acc_init();
int acc_motion_bit();
void acc_delay_ms(int ms);

#endif /* ACCELEROMETER_H_ */
