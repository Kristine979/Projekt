/*
 * boss.h
 *
 *  Created on: 15. jan. 2026
 *      Author: Bruger
 */

#ifndef BOSS_H_
#define BOSS_H_
#include "defs.h"
#include "ADC.h"
#include "screens.h"
#include "ansi.h"

uint8_t IsButtonChanged(uint8_t *pb);


void BossKey(int *boss, high_score_t hs, int *change, int screen);

#endif /* BOSS_H_ */
