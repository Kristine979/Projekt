/*
 * bullets.h
 *
 *  Created on: 16. jan. 2026
 *      Author: Bruger
 */

#ifndef BULLETS_H_
#define BULLETS_H_
#include "defs.h"
#include "ship.h"
#include "sprites.h"
#include "powerups.h"

typedef struct {
int alive, x, y, power;
} bullet_t;

void assign_bullet (bullet_t *b, ship_coord_t sc, ship_size_t ss);
void draw_bullet(bullet_t *b);

#endif /* BULLETS_H_ */
