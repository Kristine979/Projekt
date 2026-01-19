/*
 * collision.h
 *
 *  Created on: 17. jan. 2026
 *      Author: carol
 */

#ifndef COLLISION_H_
#define COLLISION_H_
#include "ship.h"
#include "Astroid.h"
#include "sprites.h"


char collision(int x1, int y1, int h1, int w1, int x2, int y2, int h2, int w2);
char shipAstroidCollision(ship_coord_t *ship_coord, ship_size_t *ship_size, astroid_t *astroids, ship_hit_t *ship_hit, int diff);

#endif /* COLLISION_H_ */
