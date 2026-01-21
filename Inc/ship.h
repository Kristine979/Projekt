/*
 * ship.h
 *
 *  Created on: 13. jan. 2026
 *      Author: Kristine
 */

#ifndef SHIP_H_
#define SHIP_H_
#include "defs.h"
#include "ADC.h"
#include "sprites.h"

typedef struct {
int32_t x, y;
} ship_coord_t;

typedef struct {
int32_t x, y;
} ship_vector_t;

typedef struct {
	int hit, lives, just_hit; // parameter der angiver om skibet er ramt og hvor mange liv der er tilbage
} ship_hit_t;

void ship_vector(ship_vector_t *sv, ADC_t adc);
void draw_ship(int diff, ship_vector_t sv, ship_coord_t *sc, ship_size_t *ss, ship_hit_t *ship_hit);

#endif /* SHIP_H_ */
