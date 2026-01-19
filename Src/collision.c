/*
 * collision.c
 *
 *  Created on: 17. jan. 2026
 *      Author: carol
 */

#include "collision.h"

// takes two boxes and calculating collisions.
// boxes has x and y coordinate and height and width
char collision(
		int x1, int y1, int h1, int w1,
		int x2, int y2, int h2, int w2
	){
	char bool1 = x1 <x2 + w2;
	char bool2 = x1 + w1 > x2;
	char bool3 = y1 < y2 + h2;
	char bool4 = y1 + h1 >y2;
	return bool1 && bool2 && bool3 && bool4;
}


char shipAstroidCollision(ship_coord_t *ship_coord, ship_size_t *ship_size, astroid_t *astroids, ship_hit_t *ship_hit){
	for (int i = 0; i < 8; ++i) {
		if (collision(ship_coord->x, ship_coord->y, ship_size->h, ship_size->l,
			(int)(astroids[i]).x, (int)(astroids[i]).y, 5, 6
		)){
			//clear astroid
			astroid_clear(&astroids[i]);
			astroids[i].active = 0;
			astroids[i].x = 200; astroids[i].y = 0;
			ship_4_sprite(ship_coord->x, ship_coord->y);
			ship_hit->hit = 1; //skib hit = true (1)
			ship_hit->lives -= 1; // reducere antal liv med 1
		}
	}
	return 0;
}
