/*
 * bullets.c
 *
 *  Created on: 16. jan. 2026
 *      Author: Bruger
 */

#include "bullets.h"

void assign_bullet (bullet_t *b, ship_coord_t sc, ship_size_t ss) {
	int i;
	for (i = 0; i<MAXBULLETS; i++) {
		if (b[i].alive == 0) {
			b[i].alive = 1;
			break;
		}
	}
	b[i].x = sc.x+ss.l+1; // front of ship
	b[i].y = sc.y+1; // front of ship
}

void draw_bullet(bullet_t *b) {
	for (int i = 0; i<MAXBULLETS; i++) {
		if (b[i].alive == 1 && b[i].x + 1 < X2) {
			// set new coordinates
			b[i].x += 1;
			printf("%c[%d;%dHO", ESC, b[i].y, b[i].x);
			// erase previous bullet
			printf("%c[%d;%dH ", ESC, b[i].y, b[i].x-1);
			continue;
			}
		if (b[i].alive == 1 && b[i].x + 1 >= X2) {
			b[i].alive = 0;
			// erase previous bullet
			printf("%c[%d;%dH ", ESC, b[i].y, b[i].x);
		}
	}

}
