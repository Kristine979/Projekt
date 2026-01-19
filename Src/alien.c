/*
 * alien.c
 *
 *  Created on: 14. jan. 2026
 *      Author: carol
 */

#include "alien.h"

int is_alien_here(alien_info_t *alien, int value) {
	for (int i = 0; i<4; i++) {
		if (value > (alien[i].y-4) && value < (alien[i].y+4)) return 1;
	}
	return 0;
}

void spawn_alien(alien_info_t *alien, int j){
	int cont = 1;
	alien[j].x = X2-7;
	int random_num;
	while (cont == 1) {
		random_num = rand_range();
		cont = is_alien_here(alien, random_num);
	}
	alien[j].y = random_num;
	alien_sprite(10, alien[j].x, alien[j].y);
}

/*
void is_alien_hit(alien_info_t *alien, gbullet_t *b, uint16_t *points) {
    for (int i = 0; i<4; i++) {
    	for (int j = 0; j<MAXBULLETS; j++) {
    		if (alien[i].x < b[j].x_fp + 1 &&
    				alien[i].x + 5 > b[j].x_fp &&
					alien[i].y < b[j].y_fp + 1 &&
					alien[i].y + 3 > b[j].y_fp) { // check if aliens are hit
    			b[j].alive = 0;
    			alien_sprite(10, alien[i].x, alien[i].y);
    			setLED(0,0,1); // glow green
    			points +=  10;
    			t.alien_led_clock = 0;
    		}
    	}
    }
}
*/

void is_alien_hit(alien_info_t *alien, gbullet_t *b, uint16_t *points) {
	// return 1 if power up hits ship, 0 otherwise
	int is_x_same = 0;
	int is_y_same = 0;
	int x_coords[5];
	int y_coords[3*4];
	for (int i = 0; i<5; i++) x_coords[i] = X2-7+i;
	for (int i = 0; i<4; i++) {
		for (int j = 0; j<3; j++) y_coords[j] = alien[i].y+j;
	}
	for (int i = 0; i>MAXBULLETS; i++) {
		for (int j = 0; j<5; j++) {if (x_coords[j] == b[i].x_fp) is_x_same = 1;}
		for (int j = 0; j<3; j++) {if (y_coords[j] == b[i].y_fp) is_y_same = 1;}
		if (is_x_same == 1 && is_y_same == 1) {
			b[i].alive = 0;
			//alien_sprite(10, alien[i].x, alien[i].y);
			setLED(0,0,1); // glow green
			points +=  10;
			t.alien_led_clock = 0;
	}
	}
}
