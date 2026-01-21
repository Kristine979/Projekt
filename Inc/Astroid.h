/*
 * astroid.h
 *
 *  Created on: 12. jan. 2026
 *      Author: Albert
 */

#ifndef ASTROID_H_
#define ASTROID_H_
#include <stdint.h>
#include <stdio.h>
#include "sprites.h"
#include "ansi.h"

// Asteroid data
typedef struct {
    int16_t x;
    int16_t y;
    int16_t color;
    int8_t active;
    int8_t speed;
} astroid_t;

// astroide funktioner
void astroid_clear(astroid_t *a);
void astroid_init(astroid_t *a, int16_t y, int16_t color, int8_t speed);
void astroid_update(astroid_t *a);
void astroid_draw(const astroid_t *a);
void astroid_spawn(astroid_t astroids[], int max_astroids, int16_t color, int8_t speed);
int rand_range();

#endif /* ASTROID_H_ */

