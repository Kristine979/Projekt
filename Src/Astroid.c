/*
 * Astroid.c
 *
 *  Created on: 15. jan. 2026
 *      Author: Albert
 */

#include "Astroid.h"


#define ASTROID_WIDTH   6
#define ASTROID_HEIGHT  5


void astroid_clear(astroid_t *a){
	/*
	 * Clear astroid from screen
	 */
    int i;
    for (i = 0; i < ASTROID_HEIGHT; i++) {
        printf("%c[%d;%dH      ", ESC, a->y + i, a->x);
    }
}

void astroid_init(astroid_t *a, int16_t y, int16_t color, int8_t speed){
	/*
	 * Initializes the astroids
	 */
    a->x = X2-15;
    a->y = y;
    a->color = color;
    a->active = 1;
    a->speed = speed;
}


void astroid_update(astroid_t *a){
	/*
	 * Update active status of the astroid
	 */
    if (a->active == 0) return;
    astroid_clear(a);
    a->x -= a->speed;
    if (a->x <= X1) {
        a->active = 0;
    }
}


void astroid_draw(const astroid_t *a){
	/*
	 * Draw astroid
	 */
    if (a->active == 0) return;
    asteroid_sprite(a->color, a->x, a->y);
}

int rand_range() {
	/*
	 * Generate a random number within a specified range
	 * The wanted range is within the top and bottom border of the game window
	 */
	uint8_t random = rand();
	random>>=2;
	if (random>48) random -= 20;
	if (random<2) random += 1;
    return (random+1);
}

void astroid_spawn(astroid_t astroids[], int max_astroids, int16_t color, int8_t speed)
{
	// create a new astroid in an empty part of the memory
    for (int i = 0; i < max_astroids; i++) {
        if (astroids[i].active == 0) {

            int16_t y = rand_range();
            int8_t  sp = speed;
            int16_t col = color;

            astroid_init(&astroids[i], y, col, sp);
            break;
        }
    }
}
