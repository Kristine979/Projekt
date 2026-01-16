/*
 * powerups.c
 *
 *  Created on: 16. jan. 2026
 *      Author: Bruger
 */

#include "powerups.h"

int did_ship_hit_power_up(power_up_t pu, ship_coord_t sc, ship_size_t ss) {
	// return 1 if power up hits ship, 0 otherwise
	int is_x_same = 0;
	int is_y_same = 0;
	int x_coords[ss.l];
	for (int i = 0; i<ss.l; i++) x_coords[i] = sc.x+i;
	int y_coords[ss.h];
	for (int i = 0; i<ss.h; i++) y_coords[i] = sc.y+i;
	for (int i = 0; i<sizeof(x_coords); i++) if (x_coords[i] == pu.x) {is_x_same = 1; break;}
	for (int i = 0; i<sizeof(y_coords); i++) if (y_coords[i] == pu.y) {is_y_same = 1; break;}
	if (is_x_same == 1 && is_y_same == 1) return 1;
	return 0;
}

void spawn_power_up(power_up_t *pu) {
	pu->x = X2-1;
	pu->y = 20;
}

void move_power_up(power_up_t *pu, power_up_t pu_check, ship_coord_t sc, ship_size_t ss) {
	if (pu->x - 1 > 0 && did_ship_hit_power_up(pu_check, sc, ss) == 0) {
		// set new coordinates
		pu->x -= 1;
		printf("%c[%d;%dHP", ESC, pu->y, pu->x);
		// erase previous bullet
		printf("%c[%d;%dH ", ESC, pu->y, pu->x+1);
	}
	else printf("%c[%d;%dH ", ESC, pu->y, pu->x);
	pu->alive = 0;
}

