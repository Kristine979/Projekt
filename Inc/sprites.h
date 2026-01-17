/*
 * sprites.h
 *
 *  Created on: 12. jan. 2026
 *      Author: Bruger
 */

#ifndef SPRITES_H_
#define SPRITES_H_
#include "defs.h"
#include "ansi.h"

typedef struct {
	int16_t l, h; // length, height
} ship_size_t;

void alien_sprite(int color, int column, int row);
void asteroid_sprite(int color, int column, int row);
void ship_1_sprite(int column, int row, ship_size_t *ship_size);
void ship_2_sprite(int column, int row, ship_size_t *ship_size);
void ship_3_sprite(int column, int row, ship_size_t *ship_size);
void ship_4_sprite(int column, int row, ship_size_t *ship_size);

#endif /* SPRITES_H_ */
