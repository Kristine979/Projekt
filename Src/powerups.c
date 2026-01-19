/*
 * powerups.c
 *
 *  Created on: 16. jan. 2026
 *      Author: Bruger
 */

#include "powerups.h"

int did_ship_hit_power_up(power_up_t pu, ship_coord_t sc, ship_size_t ss, int *current_power_up, ship_hit_t *ship_hit) {
	// return 1 if power up hits ship, 0 otherwise
	int is_x_same = 0;
	int is_y_same = 0;
	int x_coords[ss.l];
	for (int i = 0; i<ss.l; i++) x_coords[i] = sc.x+i;
	int y_coords[ss.h];
	for (int i = 0; i<ss.h; i++) y_coords[i] = sc.y+i;
	for (int i = 0; i<ss.l; i++) {if (x_coords[i] == pu.x) is_x_same = 1;}
	for (int i = 0; i<ss.h; i++) {if (y_coords[i] == pu.y) is_y_same = 1;}
	if (is_x_same == 1 && is_y_same == 1) {
		if (pu.power == GAINLIFE) {
			setLED(0,1,0); // Blue, red, green
			ship_hit->lives += 1;
			t.five_sec_counter = 0;
			return 1;
		}
		else {
			setLED(1,0,0); // Blue, red, green
			*current_power_up = pu.power;
			t.five_sec_counter = 0;
			return 1;
		}
	}
	return 0;
}

void spawn_power_up(power_up_t *pu) {
	pu->x = X2-8;
	pu->y = 20;
}

void move_power_up(power_up_t *pu, power_up_t pu_check, ship_coord_t sc, ship_size_t ss, int *current_power_up, ship_hit_t *ship_hit) {
	if ((pu->x - 1) > 0 && did_ship_hit_power_up(pu_check, sc, ss, current_power_up, ship_hit) == 0) {
		// set new coordinates
		pu->x -= 1;
		// print correct power up
		switch (pu->power) {
		case (MULTIPLEBULLETS):
				printf("%c[%d;%dH1", ESC, pu->y, pu->x);
				break;
		case (DOUBLEDAMAGE):
				printf("%c[%d;%dH2", ESC, pu->y, pu->x);
				break;
		case (FASTERBULLETS):
				printf("%c[%d;%dH3", ESC, pu->y, pu->x);
				break;
		case (GAINLIFE):
				printf("%c[%d;%dH4", ESC, pu->y, pu->x);
				break;
		}
		// erase previous bullet
		printf("%c[%d;%dH ", ESC, pu->y, pu->x+1);
	}
	else {
		printf("%c[%d;%dH ", ESC, pu->y, pu->x);
		pu->alive = 0;
	}
}

void got_power_up() {

}
