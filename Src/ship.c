/*
 * ship.c
 *
 *  Created on: 13. jan. 2026
 *      Author: Bruger
 */

#include "ship.h"

void ship_vector(ship_vector_t *sv, ADC_t adc) {
	int offset = 1900;
	if (adc.c1 > 1800 && adc.c1 < 2000) adc.c1 = 0;
	else adc.c1 = adc.c1 - offset;
	if (adc.c2 > 1800 && adc.c2 < 2000) adc.c2 = 0;
	else adc.c2 = adc.c2 - offset;
	while (abs(adc.c1) > 1 || abs(adc.c2) > 1) {
		adc.c1 = adc.c1>>1;
		adc.c2 = adc.c2>>1;
	}
	sv->x = adc.c1;
	sv->y = adc.c2;
}

void draw_ship(int diff, ship_vector_t sv, ship_coord_t *sc, ship_size_t *ss, ship_hit_t *ship_hit){ /*TODO tilføj bool som argument*/
	if (sv.x+sc->x > 2 && sv.x+sc->x < 170 && sv.y+sc->y > 2 && sv.y+sc->y < 50 && ship_hit->hit == 0) {
		// remove current ship
		for (int iy = 0; iy<ss->h; iy++) {
			printf("%c[%ld;%ldH", ESC, sc->y+iy, sc->x);
			for (int ix = 0; ix<ss->l; ix++) {
				printf(" ");
			}
		}
		// update ship coordinates
		sc->x = sc->x+(sv.x<<1);
		sc->y = sc->y-sv.y;

		// draw correct sprite
		if (diff == 1) {
			if (ship_hit->hit == 1){
				ship_4_sprite(sc->x, sc->y);
			} else {
				ship_1_sprite(sc->x, sc->y, ss); // TODO lav if med om skibet er ramt, hvis ja vis 4 ellers vis 1
			}
		}
		if (diff == 2) {
			if (ship_hit->hit == 1){
				ship_5_sprite(sc->x, sc->y);
			} else {
				ship_2_sprite(sc->x, sc->y, ss); // TODO lav if med om skibet er ramt, hvis ja vis 4 ellers vis 1
			}
		}
		if (diff == 3) {
			if (ship_hit->hit == 1){
				ship_6_sprite(sc->x, sc->y);
			} else {
				ship_3_sprite(sc->x, sc->y, ss);
			}
		}
	}
}

//
