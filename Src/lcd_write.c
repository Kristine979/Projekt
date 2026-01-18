/*
 * lcd_write.c
 *
 *  Created on: 13. jan. 2026
 *      Author: Bruger
 */

#include "lcd_write.h"

int16_t lcd_lut(int line) {
	const int16_t lut[4] = {
			0, 128, 256, 384
	};
	return lut[line];
}

void clear_lcd(uint8_t *buffer) {
	memset(buffer,0x00,512); // resets each element of the buffer to blank space
}

void lcd_write_string(char str[], location_t loc, uint8_t *buffer) {
	int spot = loc.s + lcd_lut(loc.l);
	int ind = 0; // indent
	for (int i = 0;i<strlen(str);i++) {
		char ch = str[i];
		for (int j = 0; j<5; j++) {
				memset(buffer+spot+j+ind,character_data[ch-0x20][j],1); // Sets some elements of the buffer to specified character
				}
		ind += 6;
	}
	lcd_push_buffer(buffer);
}

//3 lives = 3 full hearts, 0 lives means 3 empty hearts
void lcd_write_heart(int lives, location_t loc, uint8_t *buffer) {
	int spot = loc.s + lcd_lut(loc.l); // starts the hearts at the right place
	int ind = 0; // indent
	for (int i = 0;i<3;i++) {
		for (int j = 0; j<5; j++) {
			if (lives -i > 0) {
				memset(buffer+spot+j+ind,character_data[0x7F-0x20][j],1); // Sets some elements of the buffer to the given hex
				memset(buffer+spot+j+ind+5,character_data[0x80-0x20][j],1);
			}
			else {
				memset(buffer+spot+j+ind,character_data[0x7F+2-0x20][j],1); // Sets some elements of the buffer to the given hex
				memset(buffer+spot+j+ind+5,character_data[0x80+2-0x20][j],1);
			}
		}
		ind += 10;
	}
	lcd_push_buffer(buffer);
}

void lcd_update(char *str, char *org_str, int *count) {
	strcpy(str, org_str);
	char new[3];
	sprintf(new, "%d", *count);
	strcat(str, new);
	*count += 1;
}
