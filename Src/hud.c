/*
 * hud.c
 *
 *  Created on: 20. jan. 2026
 *      Author: Albert
 */

#include "hud.h"

void hud_init(void) {
	/*
	 * Initialize hud
	 */
    printf("%c[%d;%dHL:", ESC, HUD_Y,   HUD_X);
    printf("%c[%d;%dHT:", ESC, HUD_Y+1, HUD_X);
    printf("%c[%d;%dHS:", ESC, HUD_Y+2, HUD_X);
    printf("%c[%d;%dHP:", ESC, HUD_Y+3, HUD_X);
}

void hud_clear(void) {
	/*
	 * clear out the hud
	 */
    for (uint8_t i = 0; i < 4; i++) {
        printf("%c[%d;%dH            ", ESC, HUD_Y+i, HUD_X);
    }
}


static void draw_lives(uint8_t lives) {
	/*
	 * Draw the lives in the hud
	 */
    printf("%c[%d;%dHLives:   ", ESC, HUD_Y, HUD_X+3);
    for (uint8_t i = 0; i < lives; i++) printf("*");
    printf("   ");
}

static void draw_time(uint8_t min, uint8_t sec) {
	/*
	 * Draws the time in the hud
	 */
    printf("%c[%d;%dHTime:    %02u:%02u", ESC,
    HUD_Y+1, HUD_X+3,
    (unsigned)min, (unsigned)sec);
}

static void draw_score(uint16_t score) {
	/*
	 * draws the score in the hud
	 */
    printf("%c[%d;%dHScore:   %u", ESC, HUD_Y+2, HUD_X+3, score);
}

static void draw_power(uint8_t p) {
	/*
	 * draws the current power up in the hud
	 */
    printf("%c[%d;%dHPowerup: ", ESC, HUD_Y+3, HUD_X+3);

    if      (p == 0) printf("NONE");
    else if (p == 1) printf("MULTI");
    else if (p == 2) printf("DMG");
    else if (p == 3) printf("FAST");
    else if (p == 4) printf("LIFE");
}

void hud_update(
    uint8_t lives,
    uint16_t score,
    uint8_t powerup,
    uint8_t min,
    uint8_t sec

) {
	/*
	 * Updates the hud
	 */
    draw_lives(lives);
    draw_time(min, sec);
    draw_score(score);
    draw_power(powerup);
}



