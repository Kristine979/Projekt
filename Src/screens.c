/*
 * screens.c
 *
 *  Created on: 13. jan. 2026
 *      Author: Bruger
 */

# include "screens.h"

void switch_screen(high_score_t hs, int *change, int screen) {
	clrscr();
	window();
	switch(screen) {
		case MENU:
			menu(); // draw menu
			break;
		case DIFF:
			difficulty(); // draw menu
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
			printf("boss");
			break;
	}
	*change = 0; // stop the screens from changing
}
