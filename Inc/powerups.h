/*
 * powerups.h
 *
 *  Created on: 16. jan. 2026
 *      Author: Bruger
 */

#ifndef POWERUPS_H_
#define POWERUPS_H_
#include "defs.h"
#include "ship.h"
#include "LED.h"
#include "clock.h"
#define NOPOWER 0
#define MULTIPLEBULLETS 1
#define DOUBLEDAMAGE 2
#define FASTERBULLETS 3
#define GAINLIFE 4

/* Powerups:
 * Multiple bullets (5)
 * double damage
 * faster bullets
 * gain life
 */

typedef struct {
int x, y, power, alive;
} power_up_t;

int did_ship_hit_power_up(power_up_t pu, ship_coord_t sc, ship_size_t ss, int *current_power_up);

void spawn_power_up(power_up_t *pu);

void move_power_up(power_up_t *pu, power_up_t pu_check, ship_coord_t sc, ship_size_t ss, int *current_power_up);

#endif /* POWERUPS_H_ */
