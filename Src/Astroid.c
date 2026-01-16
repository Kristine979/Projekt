/*
 * Astroid.c
 *
 *  Created on: 15. jan. 2026
 *      Author: alber
 */

#include "Astroid.h"
#include "sprites.h"
#include "ansi.h"
#include "stdio.h"


#define ASTROID_WIDTH   6
#define ASTROID_HEIGHT  5
#define SCREEN_LEFT     1


static void astroid_clear(const astroid_t *a){
    int i;
    for (i = 0; i < ASTROID_HEIGHT; i++) {
        printf("%c[%d;%dH      ", ESC, a->y + i, a->x);
    }
}

void astroid_init(astroid_t *a, int16_t x, int16_t y, int16_t color, int8_t speed){
    a->x = x;
    a->y = y;
    a->color = color;
    a->active = 1;
    a->speed = speed;
}

void astroid_update(astroid_t *a){
    if (a->active == 0) return;
    astroid_clear(a);
    a->x -= a->speed;
    if (a->x <= SCREEN_LEFT) {
        a->active = 0;
    }
}

void astroid_draw(const astroid_t *a){
    if (a->active == 0) return;
    asteroid_sprite(a->color, a->x, a->y);
}

void astroid_spawn(astroid_t astroids[], int max_astroids,
                   int16_t start_x, int16_t color, int8_t speed)
{
    int i;

    for (i = 0; i < max_astroids; i++) {
        if (astroids[i].active == 0) {
            astroid_init(&astroids[i],
                         start_x,
                         5 + i * 6,   // forskellig y
                         color,
                         speed);
            break;  // kun én spawn
        }
    }
}

