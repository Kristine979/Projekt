/*
 * hud.h
 *
 *  Created on: 20. jan. 2026
 *      Author: Albert
 */
#ifndef HUD_H_
#define HUD_H_

#include "defs.h"
#include <stdint.h>
#include <stdio.h>


#define HUD_X 2
#define HUD_Y (Y2 + 2)


void hud_init(void);
void hud_clear(void);

void hud_update(
    uint8_t lives,
    uint16_t score,
    uint8_t powerup,
    uint8_t min,
    uint8_t sec
);


#endif

