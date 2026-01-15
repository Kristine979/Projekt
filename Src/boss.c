/*
 * boss.c
 *
 *  Created on: 15. jan. 2026
 *      Author: Bruger
 */


#include "boss.h"

uint8_t IsButtonChanged(uint8_t *pb) {
	if (*pb!=button()) {
		*pb=button();
		return button();
	}
	else return NOPUSH;
}


void BossKey(int *boss, high_score_t hs, int *change, int screen) {
	if (boss == 0) {clrscr(); printf("BOSS"); *boss = 1;}
	else {switch_screen(hs, change, screen);*boss = 0;}
}
