/*
 * ship.h
 *
 *  Created on: 13. jan. 2026
 *      Author: Bruger
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

void ship_vector(ship_vector_t *sv, ADC_t adc);
void draw_ship(int diff, ship_vector_t sv, ship_coord_t *sc, ship_size_t *ss);

#endif /* SHIP_H_ */
