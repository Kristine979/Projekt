/*
 * screens.h
 *
 *  Created on: 13. jan. 2026
 *      Author: Bruger
 */

#ifndef SCREENS_H_
#define SCREENS_H_
#include "defs.h"
#include "menu.h"
#include "HighScore.h"
#include "Difficulty.h"
#include "Help.h"

void switch_screen(high_score_t hs, int *change, int screen, ArrowState *a);

#endif /* SCREENS_H_ */
