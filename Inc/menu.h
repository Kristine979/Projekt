/*
 * menu.h
 *
 *  Created on: 12. jan. 2026
 *      Author: Bruger
 */

#ifndef MENU_H_
#define MENU_H_
#include "stm32f30x_conf.h" // STM32 config
#include "30010_io.h" // Input/output library for this course
#include "defs.h"
#include "window.h"
#include "ansi.h"
#include "ADC.h"
#include "stdint.h"


typedef struct
{
    uint8_t index;
    int8_t  lastDir;
} ArrowState;


void Arrow_Init(ArrowState *arrow);
void Arrow_Update(ArrowState *arrow, int32_t adcY);
static int8_t adcToDir(uint16_t adc);
static void eraseArrow(uint8_t index);




void PrintText(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t num, char text[]);
void menu();

#endif /* MENU_H_ */
