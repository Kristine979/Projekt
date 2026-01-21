/*
 * screens.h
 *
 *  Created on: 13. jan. 2026
 *      Author: Kristine
 */

#ifndef SCREENS_H_
#define SCREENS_H_
#include "defs.h"
#include "menu.h"
#include "HighScore.h"
#include "DifficultyScreen.h"
#include "HelpScreen.h"
#include "DeathScreen.h"
#include "NextLevelScreen.h"
#include "YouWinScreen.h"
#include "BossScreen.h"

void switch_screen(high_score_t hs, int *change, int screen, ArrowState *a, int alien_amount);

#endif /* SCREENS_H_ */
