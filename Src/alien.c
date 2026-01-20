/*
 * alien.c
 *
 *  Created on: 14. jan. 2026
 *      Author: carol
 */

#include "alien.h"

int is_alien_here(alien_info_t *alien, int value, int alien_amount) {
	for (int i = 0; i<alien_amount; i++) {
		if (value > (alien[i].y-4) && value < (alien[i].y+4)) return 1;
	}
	return 0;
}

void spawn_alien(alien_info_t *alien, int j, int alien_amount){
	int cont = 1;
	alien[j].x = X2-7;
	int random_num;
	while (cont == 1) {
		random_num = rand_range();
		cont = is_alien_here(alien, random_num, alien_amount);
	}
	alien[j].y = random_num;
	alien_sprite(10, alien[j].x, alien[j].y);
}


void is_alien_hit(alien_info_t *alien, gbullet_t *b, int16_t *points, int alien_amount) {
    for (int i = 0; i<alien_amount; i++) {
    	for (int j = 0; j<MAXBULLETS; j++) {
    		if (collision(alien[i].x, alien[i].y, 3,5, b[j].x_fp>>8, b[j].y_fp>>8, 1, 1) && b[j].alive == 1) { // check if aliens are hit
    			b[j].alive = 0;
    			alien_sprite(10, alien[i].x, alien[i].y);
    			setLED(0,0,1); // glow green
    			*points +=  10;
    			t.alien_led_clock = 0;
    			alien[i].lives -= 1;
    		}
    	}
    }
}

void is_alien_alive(alien_info_t alien[], int *change, int *screen, int alien_amount) {
	int count = 0;
	for (int i = 0; i<alien_amount; i++) {
		if (alien[i].lives <= 0) {
			printf("%c[%d;%dH     ", ESC, alien[i].y, alien[i].x);
			printf("%c[%d;%dH     ", ESC, alien[i].y+1, alien[i].x);
			printf("%c[%d;%dH     ", ESC, alien[i].y+2, alien[i].x);
			count += 1;
		}
	}
	if (count >= alien_amount) {*change=1; *screen = NEXTLEVEL; t.five_sec_counter = 0;}
}
