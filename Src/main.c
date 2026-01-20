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
#include "Astroid.h"
#include "boss.h"
#include "powerups.h"
#include "LED.h"
#include "accelerometer.h"
#include "collision.h"
#include "gravity_bullets.h"

#define max_astroids 8
#define astroid_spawntime 5
#define DT_FP 13   // ~0.05 in Q8 (13/256)

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
/*
int main(void) // Aliens
{
	uart_init(230400);
	clrscr();
	ArrowState arrow = {0,0};
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
			switch_screen(hs, &change, screen, &arrow);
			spawn(0, 0, 0);
			spawn(1, 10, 15);
			spawn(2, 20, 30);
			spawn(3, 7, 45);
			ship_4_sprite(120, 10);
			ship_5_sprite(120, 15);
			ship_6_sprite(120, 20);
		}

		if (t.s >= 2){
			update_alien(0);
			update_alien(1);
			update_alien(2);
			update_alien(3);
	}
}
}*/



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
	acc_init();

	// lcd
	uint8_t buffer[512]; // set up buffer for lcd
	clear_lcd(buffer); // clear lcd screen
	char str[25]; // string used to write to lcd
	char string[15];

	// struct initializers
	ADC_t adc;
	location_t loc = {0, 1}; // setup location on lcd, defining slice (s) and line (l)
	ship_vector_t ship_vec = {};
	ship_coord_t ship_coordinate = {90, 25};
	ship_size_t ship_size = {0,0};
	ship_hit_t ship_hit = {0,3}; // initialisere at skibet ikke er ramt og der er 3 liv tilbage
	high_score_t hs = {}; // initialize high score structure and set to 0
	gbullet_t gbullets[MAXBULLETS] = {{}}; //gravitation
	grav_source_t grav[max_astroids]; // gravitation
	alien_info_t aliens[9] = {};
	power_up_t PowerUp = {0,0,1,0};
	ArrowState arrow = {0,0};

	// variables initializers
	int screen = MENU, change = 1, difficulty = 1; // int to decide what screen is shown, and change to know whether the screen needs to change
	int prev_screen; // go from normal screen to boss key and back, depending on value
	uint8_t PushButton = button(), CheckButton = button();
	int shoot = 0, current_power_up = NOPOWER, faster_bullets;
	int16_t points = 0;
	int alien_amount = 2;
	int astroid_modifier = 14;

	// astroid initializers
	astroid_t astroids[max_astroids] = {};
	int astroid_timer = 0;

	gbullets_init(gbullets, MAXBULLETS); //gravity

	// for at få spillet til at virke uden joystick
	/*
	change = 1;
	screen = GAME;
	difficulty = 1;
	*/

	while(1){
		loc.l = 3;
		sprintf(str, "x: %ld, y: %ld  ", ship_coordinate.x, ship_coordinate.y);
		lcd_write_string(str, loc, buffer);

		// check if there's still health, and reset if health is 0
		if (ship_hit.lives <= 0) {
			screen = GAMEOVER;
			change = 1;
			ship_hit.lives = 3;
			for (int i = 0; i < max_astroids; i++) {
				astroids[i].active=0;
			}
			PowerUp.alive = 0; PowerUp.power = 1; PowerUp.x = X2-1;
			update_hs(&hs, points);
			alien_amount = 2;
			ship_coordinate.x = 90; ship_coordinate.y = 20;
			astroid_modifier = 16;
		}

		// check if button have been pressed
		CheckButton = IsButtonChanged(&PushButton);
		if (CheckButton==WHITE) {
			switch (screen) {
			case MENU:
				Arrow_Clear(&arrow);
				change = 1;
				screen = arrow.index+1;
				break;
			case HS:
			case HELP:
			case GAMEOVER:
				change = 1;
				screen = MENU;
				setLED(0,0,0);
				break;
			case DIFF:
				change = 1;
				screen = GAME;
				if (arrow.index == 0) difficulty = 1;
				if (arrow.index == 1) difficulty = 2;
				if (arrow.index == 2) difficulty = 3;
				break;
			case GAME:
				shoot = 1;
				break;
			}
		}
		if (CheckButton==RED) {
			if (screen != BOSS) {change = 1; prev_screen = screen; screen = BOSS;}
			else {change = 1; screen = prev_screen;}
		}

		// check if ADC have been changed
		check_ADC(&adc);

		// LCD setup
		loc.l = 2;
		sprintf(string, "%04ld, %04ld", adc.c1, adc.c2);
		lcd_write_string(string, loc, buffer);
		if (t.five_sec_counter == 30 || t.alien_led_clock == 3) {
			setLED(0,0,0);
			if (current_power_up == STRONGERBULLETS) erase_strong_bullets(gbullets);
			current_power_up = NOPOWER;
		}
		loc.l = 1;
		lcd_write_heart(ship_hit.lives, loc, buffer);

		// counter on LCD
		if (t.counter_flag == 1) {
			t.counter_flag = 0;
			loc.l = 1;
			sprintf(str, "min: %02ld, s: %02ld", t.m, t.s);
			lcd_write_string(str, loc, buffer);
		}

		if (change !=0) {
			switch_screen(hs, &change, screen, &arrow); // Switch screens if necessary
			if (screen == GAME) {
				for (int i = 0; i<alien_amount; i++) {
					aliens[i].lives = 2;
					spawn_alien(aliens, i, alien_amount);
				}
			}
		}

		// game play
		switch(screen) {
			case MENU:
				Arrow_Update(&arrow, adc.c2);   // Flytter kun pilen
				break;
			case DIFF:
				Arrow_Update(&arrow, adc.c2);   // Flytter kun pilen
				break;
			case HS:
				break;
			case HELP:
				break;
			case GAME:
				// check if any aliens are alive
				is_alien_alive(aliens, &change, &screen, alien_amount);

				if(ship_hit.hit==1){
					if (acc_motion_bit() == 1){
						ship_hit.hit = 0;
						setLED(0,0,0); // turn off LED
					}
				}
				// collision check between alien and bullet
				is_alien_hit(aliens, gbullets, &points, alien_amount);

				// update asteroid position
				if (t.astroid_flag > astroid_modifier) {
					t.astroid_flag = 0;
					astroid_timer++;
					if (astroid_timer >= astroid_spawntime){
						astroid_timer = 0;
						astroid_spawn(astroids, max_astroids, 8, 3);
					}
					for (int i=0; i<max_astroids; i++){
						astroid_update(&astroids[i]);
						astroid_draw(&astroids[i]);
					}
					//collision check between astroids and ship
					shipAstroidCollision(&ship_coordinate, &ship_size, astroids, &ship_hit, difficulty, &points);
				}
				if (t.ship_clock > difficulty) {
					t.ship_clock = 0;
					ship_vector(&ship_vec, adc);

					draw_ship(difficulty, ship_vec, &ship_coordinate, &ship_size, &ship_hit);

					loc.l = 0;
					sprintf(str, "%d", current_power_up);
					lcd_write_string(str, loc, buffer);

					//collision check between astroids and ship
					shipAstroidCollision(&ship_coordinate, &ship_size, astroids, &ship_hit, difficulty, &points);
				}

				// bullets and powerup
				if (current_power_up != FASTERBULLETS) faster_bullets = 1;
				else faster_bullets = 0;
				if (t.bullet_flag > faster_bullets) {
				    t.bullet_flag = 0;
				    int gN = 0;
				    for (int k = 0; k < max_astroids; k++) {
				        if (astroids[k].active) {
				            grav[gN].x  = astroids[k].x;
				            grav[gN].y  = astroids[k].y;
				            grav[gN].w  = 6;
				            grav[gN].h  = 5;
				            grav[gN].mu = 150; //Gravity power
				            gN++;
				        }
				    }

				    if (shoot == 1) {
				        shoot = 0;
				        if (current_power_up != MULTIPLEBULLETS) {
				        gbullet_spawn_from_ship(gbullets, MAXBULLETS, ship_coordinate, ship_size,
				                                60 * FP_ONE, 0, current_power_up);
				        }
				        else if (current_power_up == MULTIPLEBULLETS) { // multiple bullets
					        gbullet_spawn_from_ship(gbullets, MAXBULLETS, ship_coordinate, ship_size,
					                                60 * FP_ONE, 0, current_power_up);
					        gbullet_spawn_from_ship(gbullets, MAXBULLETS, ship_coordinate, ship_size,
					                                60 * FP_ONE, 10<<8, current_power_up);
					        gbullet_spawn_from_ship(gbullets, MAXBULLETS, ship_coordinate, ship_size,
					                                60 * FP_ONE, 20<<8, current_power_up);
					        gbullet_spawn_from_ship(gbullets, MAXBULLETS, ship_coordinate, ship_size,
					                                60 * FP_ONE, -10<<8, current_power_up);
					        gbullet_spawn_from_ship(gbullets, MAXBULLETS, ship_coordinate, ship_size,
					                                60 * FP_ONE, -20<<8, current_power_up);
				        }
				    }
				    if (current_power_up != STRONGERBULLETS) gbullets_step_and_draw(gbullets, MAXBULLETS, grav, gN,
				    		DT_FP, current_power_up);
				    else draw_strong_bullet(gbullets);

				    // PowerUp stays the same in both modes
				    if (PowerUp.alive == 1) {
				        move_power_up(&PowerUp, PowerUp, ship_coordinate, ship_size, &current_power_up, &ship_hit);
				    }
				}

				// spawn power up
				if (t.pu_flag == 1) {
					spawn_power_up(&PowerUp);
					PowerUp.alive = 1;
					t.pu_flag = 0;
					if (PowerUp.power < 4) PowerUp.power += 1;
					else PowerUp.power = 1;
				}
				break;
			case GAMEOVER:
				break;
			case BOSS:
				break;
			case NEXTLEVEL:
				if (t.five_sec_counter > 5) {
					change = 1;
					screen = GAME;
					alien_amount += 1;
					astroid_modifier -= 2;
					for (int i = 0; i<MAXBULLETS; i++) gbullets->alive = 0;
				}
				break;
		}
	}
}
