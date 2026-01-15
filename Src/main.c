#include "stm32f30x_conf.h" // STM32 config
#include "30010_io.h" 		// Input/output library for this course
#include "ansi.h"
#include "window.h"
#include "menu.h"
#include "defs.h"
#include "HighScore.h"
#include "sprites.h"
#include "clock.h"
#include "charset.h"
#include "lcd_write.h"
#include "ADC.h"
#include "screens.h"
#include "ship.h"

/*
int main(void) // test main
{
	uart_init(230400);
	clrscr();
	clock_init(); // initialize timer
	lcd_init(); // initialize lcd
	uint8_t buffer[512]; // set up buffer for lcd
	clear_lcd(buffer); // clear lcd screen
	location_t loc = {0, 1}; // setup location on lcd, defining slice (s) and line (l)
	printf("%c\x1B[?25l", ESC); // hide cursor, \x1B[?25h to show, \x1B[?25l to hide
	high_score_t hs = {1100, 900, 100, 0, 0}; // initialize high score structure and set to 0
	update_hs(&hs, 200);
	window(); // draw window
	menu(); // draw menu
	hs_menu(hs); // draw high scores
	char str[25]; // string used to write to lcd
	alien_sprite(10, 170, 10);
	asteroid_sprite(8, 140, 10);
	ship_1_sprite(120, 10);
	ship_2_sprite(120, 15);
	ship_3_sprite(120, 20);
	lcd_write_heart(2, loc, buffer); // full_heart for filling, empty_heart for empty
	loc.l = 2;
	while(1){
		if (t.cs == 1) {
			sprintf(str, "t: %ld, min: %ld, s: %ld", t.h, t.m, t.s);
			lcd_write_string(str, loc, buffer);
		}
	}
}
*/

int main(void)
{
	uart_init(230400);
	printf("hi");
	clrscr();
	clock_init(); // initialize timer
	lcd_init(); // initialize lcd
	ADC_init();
	uint8_t buffer[512]; // set up buffer for lcd
	clear_lcd(buffer); // clear lcd screen
	ADC_t adc;
	location_t loc = {0, 1}; // setup location on lcd, defining slice (s) and line (l)
	ship_vector_t ship_vec;
	ship_coord_t ship_coordinate = {90, 25};
	ship_size_t ship_size;
	int screen = MENU, change = 0, difficulty = 1; // int to decide what screen is shown, and change to know whether the screen needs to change
	high_score_t hs; // initialize high score structure and set to 0
	printf("%c\x1B[?25l", ESC); // hide cursor, \x1B[?25h to show, \x1B[?25l to hide
	window(); // draw window
	menu(); // draw menu
	char str[25]; // string used to write to lcd
	ArrowState arrow;
	ADC_init();
	Arrow_Init(&arrow);     // Tegner pilen ved (4,8)
	while(1){
		ADC_measure(&adc);
		char string[15];
		loc.l = 2;
		sprintf(string, "%04ld, %04ld", adc.c1, adc.c2);
		lcd_write_string(string, loc, buffer);
		if (t.cs == 1) {
			loc.l = 1;
			sprintf(str, "t: %ld, min: %ld, s: %ld", t.h, t.m, t.s);
			lcd_write_string(str, loc, buffer);
		}
		if (change !=0) switch_screen(hs, &change, screen);
		if (t.s == 1 && t.cs == 1) {change = 1; screen = GAME;}
		// game play
		switch(screen) {
			case MENU:

				break;
			case HS:
				break;
			case HELP:
				break;
			case GAME:
				if (t.cs == 1 || t.cs == 50) {
					ship_vector(&ship_vec, adc);
					draw_ship(difficulty, ship_vec, &ship_coordinate, &ship_size);
					loc.l = 0;
					sprintf(str, "vx: %ld, vy: %ld", ship_vec.x, ship_vec.y);
					lcd_write_string(str, loc, buffer);
					loc.l = 3;
					sprintf(str, "x: %ld, y: %ld", ship_coordinate.x, ship_coordinate.y);
					lcd_write_string(str, loc, buffer);
				}
				break;
			case BOSS:
				break;
		Arrow_Update(&arrow, adc.c2);   // Flytter kun pilen
		}
	}
}

