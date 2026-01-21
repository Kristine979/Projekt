/*
 * screens.c
 *
 *  Created on: 13. jan. 2026
 *      Author: Bruger
 */

#include "screens.h"

void switch_screen(high_score_t hs, int *change, int screen, ArrowState *a, int alien_amount){
	clrscr();
	window();
	switch(screen) {
		case MENU:
			menu(); // draw menu
			Arrow_init(a);
			break;
		case DIFF:
			difficulty(); // draw menu
			Arrow_init(a);
			break;
		case HS:
			hs_menu(hs); // draw high scores
			break;
		case HELP:
			help();
			break;
		case GAME:
			break;
		case BOSS:
			boss(2, 53);
			break;
		case GAMEOVER:
			Death();
			break;
		case NEXTLEVEL:
			if (alien_amount < 9) NextLevelScreen();
			break;
		case WIN:
			youwin();
			break;
	}
	*change = 0; // stop the screens from changing
}
