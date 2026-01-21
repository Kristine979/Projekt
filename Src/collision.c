/*
 * collision.c
 *
 *  Created on: 17. jan. 2026
 *      Author: Caroline
 */

#include "collision.h"

char collision(
		int x1, int y1, int h1, int w1,
		int x2, int y2, int h2, int w2
	){
	/*
	 * takes two boxes and calculates collisions.
	 * boxes has x and y coordinate and height and width
	 */
	char bool1 = x1 <x2 + w2;
	char bool2 = x1 + w1 > x2;
	char bool3 = y1 < y2 + h2;
	char bool4 = y1 + h1 >y2;
	return bool1 && bool2 && bool3 && bool4;
}


char shipAstroidCollision(ship_coord_t *ship_coord, ship_size_t *ship_size, astroid_t *astroids,
		ship_hit_t *ship_hit, int diff, int16_t *points){
	/*
	 * Checks whether the ship is colliding with an astroid
	 * redraw the avatar if necessary
	 */
	for (int i = 0; i < 8; ++i) { // run through all astroids
		if (collision(ship_coord->x, ship_coord->y, ship_size->h, ship_size->l,
			(int)(astroids[i]).x, (int)(astroids[i]).y, 5, 6
		)){
			//clear astroid if necessary
			astroid_clear(&astroids[i]);
			astroids[i].active = 0;
			astroids[i].x = 200; astroids[i].y = 0;
			// redraw avatar
			switch (diff) {
			case 1:
				ship_4_sprite(ship_coord->x, ship_coord->y);
				break;
			case 2:
				ship_5_sprite(ship_coord->x, ship_coord->y);
				break;
			case 3:
				ship_6_sprite(ship_coord->x, ship_coord->y);
				break;
			}
			ship_hit->hit = 1; //ship hit = true (1)
			ship_hit->lives -= 1; // reduce lives by 1
			ship_hit->just_hit = 1;
			if (*points >= 5) *points -= 5;
			setLED(1,1,1); // glow white while stuck
		}
	}
	return 0;
}
