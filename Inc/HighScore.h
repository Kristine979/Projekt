/*
 * HighScore.h
 *
 *  Created on: 12. jan. 2026
 *      Author: Bruger
 */

#ifndef HIGHSCORE_H_
#define HIGHSCORE_H_
#include "defs.h"

typedef struct {
int32_t h1,h2,h3,h4,h5;
} high_score_t;

void update_hs(high_score_t *hs, uint16_t new_score);
void hs_menu(high_score_t hs);

#endif /* HIGHSCORE_H_ */
