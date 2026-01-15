/*
 * sprites.c
 *
 *  Created on: 12. jan. 2026
 *      Author: Bruger
 */

#include "sprites.h"

void alien_sprite(int color, int column, int row) {
	fgcolor(color);
	printf("%c[%d;%dH\xDB\xDB \xDB\xDB", ESC, row, column);
	printf("%c[%d;%dH\xDB \xDB \xDB", ESC, row+1, column);
	printf("%c[%d;%dH \xDB \xDB ", ESC, row+2, column);
	resetbgcolor();
}

void asteroid_sprite(int color, int column, int row) {
	fgcolor(color);
	printf("%c[%d;%dH \xDC\xDB\xDB\xDC ", ESC, row, column);
	printf("%c[%d;%dH\xDB\xDB\xDB\xDB\xDB\xDB", ESC, row+1, column);
	printf("%c[%d;%dH\xDB\xDB\xDB\xDB\xDB\xDB", ESC, row+2, column);
	printf("%c[%d;%dH\xDB\xDB\xDB\xDB\xDB\xDB", ESC, row+3, column);
	printf("%c[%d;%dH \xDF\xDB\xDB\xDF ", ESC, row+4, column);
	resetbgcolor();
}

void ship_1_sprite(int column, int row, ship_size_t *ship_size) {
	printf("%c[%d;%dH   \x5F\x5F ", ESC, row, column);
	printf("%c[%d;%dH\xAF\x3D\x3C \x6F\x3E", ESC, row+1, column);
	printf("%c[%d;%dH   \xEE\xEE ", ESC, row+2, column);
	ship_size ->l = 6;
	ship_size ->h = 3;

}

void ship_2_sprite(int column, int row, ship_size_t *ship_size) {
	printf("%c[%d;%dH   \x5C ", ESC, row, column);
	printf("%c[%d;%dH\xAF\x3D\x28\x6F\x3E", ESC, row+1, column);
	printf("%c[%d;%dH   \x2F ", ESC, row+2, column);
	ship_size ->l = 5;
	ship_size ->h = 3;
}

void ship_3_sprite(int column, int row, ship_size_t *ship_size) {
	printf("%c[%d;%dH   \x5F\x5F\x5C\x5F  ", ESC, row, column);
	printf("%c[%d;%dH\xAF\x3D\x2F   \x28\x6F\x3E", ESC, row+1, column);
	printf("%c[%d;%dH   \xEE\xEE\x2F\xEE  ", ESC, row+2, column);
	ship_size ->l = 9;
	ship_size ->h = 3;
}

