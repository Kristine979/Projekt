/*
 * accelerometer.h
 *
 *  Created on: 15. jan. 2026
 *      Author: carol
 */

#ifndef ACCELEROMETER_H_
#define ACCELEROMETER_H_

#define ESC 0x1B

void acc_init(void);
int acc_motion_bit(void);
void acc_delay_ms(int ms);

#endif /* ACCELEROMETER_H_ */
