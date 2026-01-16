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
#include "Difficulty.h"
#include "alien.h"
#include "boss.h"
#include "bullets.h"
#include "powerups.h"
#include "LED.h"

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

int main(void) // Aliens
{
	uart_init(230400);
	clrscr();
	clock_init(); // initialize timer
	lcd_init(); // initialize lcd
	uint8_t buffer[512]; // set up buffer for lcd
	clear_lcd(buffer); // clear lcd screen
	location_t loc = {0, 1}; // setup location on lcd, defining slice (s) and line (l)
	printf("%c\x1B[?25l", ESC); // hide cursor, \x1B[?25h to show, \x1B[?25l to hide
	window(); // draw window
	difficulty(); // draw menu
	char str[25]; // string used to write to lcd
	alien_sprite(10, 170, 10);
	asteroid_sprite(8, 140, 10);
	lcd_write_heart(2, loc, buffer); // full_heart for filling, empty_heart for empty
	loc.l = 2;
	int change = 0, screen = MENU;
	high_score_t hs; // initialize high score structure and set to 0
	while(1){
		if (t.cs == 1) {
			sprintf(str, "t: %ld, min: %ld, s: %ld", t.h, t.m, t.s);
			lcd_write_string(str, loc, buffer);

		}
		if (t.s == 1) {change = 1; screen = GAME;}
		if (change !=0) {
			switch_screen(hs, &change, screen);
			spawn(0, 0, 0);
			spawn(1, 10, 15);
			spawn(2, 20, 30);
			spawn(3, 7, 45);
		}

		if (t.s >= 2){
			update_alien(0);
			update_alien(1);
			update_alien(2);
			update_alien(3);
	}
}
}
*/


int main(void)
{
	uart_init(230400);
	clrscr();
	printf("%c\x1B[?25l", ESC); // hide cursor, \x1B[?25h to show, \x1B[?25l to hide

	// initializers
	clock_init(); // initialize timer
	lcd_init(); // initialize lcd
	ADC_init();
	led_init();
	setLED(0,0,0); // no light

	// lcd
	uint8_t buffer[512]; // set up buffer for lcd
	clear_lcd(buffer); // clear lcd screen
	char str[25]; // string used to write to lcd

	// struct initializers
	ADC_t adc;
	location_t loc = {0, 1}; // setup location on lcd, defining slice (s) and line (l)
	ship_vector_t ship_vec = {};
	ship_coord_t ship_coordinate = {90, 25};
	ship_size_t ship_size = {0,0};
	high_score_t hs = {}; // initialize high score structure and set to 0
	bullet_t bullet[MAXBULLETS];
	power_up_t PowerUp = {};

	// variables initializers
	int screen = MENU, change = 0, difficulty = 1; // int to decide what screen is shown, and change to know whether the screen needs to change
	int prev_screen; // go from normal screen to boss key and back, depending on value
	uint8_t PushButton = button(), CheckButton = button();
	int shoot = 0, current_power_up = NOPOWER;

	// draw screen
	window(); // draw window
	menu(); // draw menu
	ArrowState arrow;
	Arrow_Init(&arrow);     // Tegner pilen ved (4,8)

	while(1){
		// check if button have been pressed
		CheckButton = IsButtonChanged(&PushButton);
		if (CheckButton==WHITE) {
			if (screen == MENU) {change = 1; screen = arrow.index+1;}
			else if (screen == HS || screen == DIFF || screen == HELP) {change = 1; screen = MENU;}
			else if (screen == GAME) {shoot = 1;}
		}
		if (CheckButton==RED) {
			if (screen != BOSS) {change = 1; prev_screen = screen; screen = BOSS;}
			else {change = 1; screen = prev_screen;}
		}

		// check if ADC have been changed
		ADC_config(2);   // joystick Y
		ADC_measure(&adc);

		// LCD setup
		char string[15];
		loc.l = 2;
		sprintf(string, "%04ld, %04ld", adc.c1, adc.c2);
		lcd_write_string(string, loc, buffer);
		if (t.five_sec_counter >= 5) setLED(0,0,0);

		// counter on LCD
		if (t.counter_flag == 1) {
			t.counter_flag = 0;
			loc.l = 1;
			sprintf(str, "t: %02ld, min: %02ld, s: %02ld", t.h, t.m, t.s);
			lcd_write_string(str, loc, buffer);
		}

		if (change !=0) switch_screen(hs, &change, screen); // Switch screens if necessary
		if (t.one_sec_flag == 1) {change = 1; screen = GAME; t.one_sec_flag = 0;} // buffer code to get correct screen for checking code

		// game play
		switch(screen) {
			case MENU:
				Arrow_Update(&arrow, adc.c2);   // Flytter kun pilen
				break;
			case DIFF:
				break;
			case HS:
				break;
			case HELP:
				break;
			case GAME:
				if (t.flag == 1) {
					t.flag = 0;
					ship_vector(&ship_vec, adc);
					draw_ship(difficulty, ship_vec, &ship_coordinate, &ship_size);
					loc.l = 0;
					sprintf(str, "vx: %ld, vy: %ld", ship_vec.x, ship_vec.y);
					lcd_write_string(str, loc, buffer);
					loc.l = 3;
					sprintf(str, "x: %ld, y: %ld", ship_coordinate.x, ship_coordinate.y);
					lcd_write_string(str, loc, buffer);
				}
				if (t.bullet_flag == 1) {
					// bullets
					t.bullet_flag = 0;
					if (shoot == 1) {
						shoot = 0;
						assign_bullet (&bullet, ship_coordinate, ship_size);
					}
					draw_bullet(&bullet);

					// move power up symbol
					if (PowerUp.alive == 1)	{
						move_power_up(&PowerUp, PowerUp, ship_coordinate, ship_size);
					}
				}
				// spawn power up
				if (t.pu_flag == 1) {
					spawn_power_up(&PowerUp);
					PowerUp.alive = 1;
					t.pu_flag = 0;
					if (PowerUp.power > 4) PowerUp.power += 1;
					else PowerUp.power = 1;
				}
				break;
			case BOSS:
				break;
		}
	}
}





