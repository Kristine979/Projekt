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


