/*
 * screens.c
 *
 *  Created on: 13. jan. 2026
 *      Author: Bruger
 */

#include "screens.h"

void switch_screen(high_score_t hs, int *change, int screen, ArrowState *a){
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
			// print out "BOSS" in big letters, one line at a time
			printf("%c[%d;%dH###   ###   ###  ###", ESC, 6, 30);
			printf("%c[%d;%dH#  # #   # #    #", ESC, 7, 30);
			printf("%c[%d;%dH###  #   #  ##   ##", ESC, 8, 30);
			printf("%c[%d;%dH#  # #   #    #    #", ESC, 9, 30);
			printf("%c[%d;%dH###   ###  ###  ###", ESC, 10, 30);
			break;
		case GAMEOVER:
			printf("%c[%d;%dH###   ###  ", ESC, 6, 30);
			printf("%c[%d;%dH#  # #   # ", ESC, 7, 30);
			printf("%c[%d;%dH###  #   # ", ESC, 8, 30);
			printf("%c[%d;%dH#  # #   # ", ESC, 9, 30);
			printf("%c[%d;%dH###   ###  ", ESC, 10, 30);
			break;
	}
	*change = 0; // stop the screens from changing
}
