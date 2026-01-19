/*
 * alien.h
 *
 *  Created on: 14. jan. 2026
 *      Author: carol
 */

#ifndef ALIEN_H_
#define ALIEN_H_

#include <stdio.h>
#include "sprites.h"
#include "defs.h"
#include "Astroid.h"
#include "collision.h"
#include "gravity_bullets.h"
#include "clock.h"
#include "LED.h"

typedef struct {
	int lives;
	int x;
	int y;
} alien_info_t;

int is_alien_here(alien_info_t *alien, int value);
void spawn_alien(alien_info_t *alien, int j);
void is_alien_hit(alien_info_t *alien, gbullet_t *b, uint16_t *points);

#endif /* ALIEN_H_ */
