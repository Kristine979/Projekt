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
#include "hud.h"

#define max_astroids 8
#define astroid_spawntime 5
#define DT_FP 13   // ~0.05 in Q8 (13/256)

int main(void)
{
	uart_init(230400);
	clrscr();
	printf("%c\x1B[?25l", ESC); // hide cursor, \x1B[?25h to show, \x1B[?25l to hide

	// initializers
	clock_init(); hud_init(); lcd_init();
	ADC_init(); led_init(); setLED(0,0,0);
	acc_init();

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
	int shoot = 0, current_power_up = NOPOWER, faster_bullets; int16_t points = 0;
	int alien_amount = 8; int astroid_modifier = 14;

	// astroid initializers
	astroid_t astroids[max_astroids] = {}; int astroid_timer = 0;
	gbullets_init(gbullets, MAXBULLETS); //gravity

	while(1){
		// check if there's still health, and reset if health is 0
		if (ship_hit.lives <= 0) {
			screen = GAMEOVER;
			change = 1;
			ship_hit.lives = 3;
			ship_hit.hit = 0;
			for (int i = 0; i < max_astroids; i++) {
				astroids[i].active=0;
			}
			PowerUp.alive = 0; PowerUp.power = 1; PowerUp.x = X2-1;
			update_hs(&hs, points);
			points = 0;
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
			case WIN:
				change = 1;
				screen = MENU;
				setLED(0,0,0);
				break;
			case DIFF:
				change = 1;
				screen = GAME;
				t.m = 0; t.s = 0;
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
		if (t.five_sec_counter == 30 || t.alien_led_clock == 3) {
			setLED(0,0,0);
			if (current_power_up == STRONGERBULLETS) erase_strong_bullets(gbullets);
			current_power_up = NOPOWER;
		}

		// print out on LCD and HUD
		if (t.counter_flag == 1) {
			t.counter_flag = 0;
			//lives
			loc.l = 0;
			lcd_write_heart(ship_hit.lives, loc, buffer);
			//timer
			loc.l = 1;
			sprintf(str, "min: %02ld, s: %02ld", t.m, t.s);
			lcd_write_string(str, loc, buffer);
			//score
			loc.l = 2;
			sprintf(str, "Score: %05d", points);
			lcd_write_string(str, loc, buffer);

			if (screen == GAME) {
				hud_update(
			    ship_hit.lives,
			    points,
			    current_power_up,
			    t.m,
			    t.s
			 );
		}
	}
		if (change !=0) {
			switch_screen(hs, &change, screen, &arrow, alien_amount); // Switch screens if necessary
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
			case DIFF:
				Arrow_Update(&arrow, adc.c2);   // Flytter kun pilen
			case HS:
			case HELP:
				hud_clear();
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
			case NEXTLEVEL:
				if (alien_amount > 8){
					screen = WIN;
					change = 1;
					ship_hit.lives = 3;
					ship_hit.hit = 0;
					for (int i = 0; i < max_astroids; i++) {
						astroids[i].active=0;
					}
					PowerUp.alive = 0; PowerUp.power = 1; PowerUp.x = X2-1;
					update_hs(&hs, points);
					points = 0;
					alien_amount = 2;
					ship_coordinate.x = 90; ship_coordinate.y = 20;
					astroid_modifier = 16;
				}
				if(t.five_sec_counter > 5) {
					change = 1;
					alien_amount += 1;
					screen = GAME;
					astroid_modifier -= 2;
					for (int i = 0; i<MAXBULLETS; i++) gbullets->alive = 0;
				}
				break;
		}
	}
}
