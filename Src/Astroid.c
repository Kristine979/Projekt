/*
 * Astroid.c
 *
 *  Created on: 15. jan. 2026
 *      Author: alber
 */

#include "Astroid.h"


#define ASTROID_WIDTH   6
#define ASTROID_HEIGHT  5


void astroid_clear(astroid_t *a){
    int i;
    for (i = 0; i < ASTROID_HEIGHT; i++) {
        printf("%c[%d;%dH      ", ESC, a->y + i, a->x);
    }
}

void astroid_init(astroid_t *a, int16_t y, int16_t color, int8_t speed){
    a->x = X2-15;
    a->y = y;
    a->color = color;
    a->active = 1;
    a->speed = speed;
}

void astroid_update(astroid_t *a){
    if (a->active == 0) return;
    astroid_clear(a);
    a->x -= a->speed;
    if (a->x <= X1) {
        a->active = 0;
    }
}

void astroid_draw(const astroid_t *a){
    if (a->active == 0) return;
    asteroid_sprite(a->color, a->x, a->y);
}

int rand_range() {
	uint8_t random = rand();
	random>>=2;
	if (random>48) random -= 20;
    return (random+1);
}

void astroid_spawn(astroid_t astroids[], int max_astroids, int16_t color, int8_t speed)
{
    for (int i = 0; i < max_astroids; i++) {
        if (astroids[i].active == 0) {

            int16_t y = rand_range();

            // evt. random speed og color også:
            int8_t  sp = speed; // eller rand_range(1, 3);
            int16_t col = color; // eller vælg fra et lille array

            astroid_init(&astroids[i], y, col, sp);
            break;
        }
    }
}
