/*
 * menu.c
 *
 *  Created on: 12. jan. 2026
 *      Author: Bruger
 */

#include "menu.h"

void PrintText(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t num, char text[]) {
	// Print out given text in a box
		box(x1,y1,x2,y2);
		printf("%c[%d;%dH%s", ESC, y1+1, x1+1, text);
		if (num == 0) {
			printf("%c[%d;%dH\x3E", ESC, y1+1, x1-1);
		}
}

void menu() {
	// print out "MENU" in big letters, one line at a time
	printf("%c[%d;%dH#   # #### #   # #   #", ESC, 2, 2);
	printf("%c[%d;%dH## ## #    ##  # #   #", ESC, 3, 2);
	printf("%c[%d;%dH# # # #### # # # #   #", ESC, 4, 2);
	printf("%c[%d;%dH#   # #    #  ## #   #", ESC, 5, 2);
	printf("%c[%d;%dH#   # #### #   #  ### ", ESC, 6, 2);
	// print Choices
	PrintText(4,7,20,9,0, "Start");
	PrintText(4,10,20,12,1, "High score");
	PrintText(4,13,20,15,1, "Help");
}
// Hello
