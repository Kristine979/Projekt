/*
 * lcd_write.h
 *
 *  Created on: 13. jan. 2026
 *      Author: Bruger
 */

#ifndef LCD_WRITE_H_
#define LCD_WRITE_H_
#define full_heart 0
#define empty_heart 2

#include "defs.h"
#include <string.h>
#include "charset.h"
#include "clock.h"

typedef struct {
int s, l; // slice, line
} location_t;

int16_t lcd_lut(int line);
void clear_lcd(uint8_t *buffer);
void lcd_write_heart(int lives, location_t loc,uint8_t *buffer);
void lcd_write_string(char str[], location_t loc,uint8_t *buffer);
void lcd_update(char *str, char *org_str, int *count);

#endif /* LCD_WRITE_H_ */
