/*
 * window.c
 *
 *  Created on: 12. jan. 2026
 *      Author: Kristine
 */

#include "window.h"

void window(){
	/*
	 * draw window in terminal
	 */
	for (int iy=1; iy<Y2+1; iy++) { // Go through each row (y)
		printf("%c[%d;%dH", ESC, iy, 1); // go to left side in window
		for (int ix=1; ix<X2+1; ix++) { // // go through each column (x)
			if ((iy==Y1 || iy==Y2) && ix>X1) printf("\xCD"); // Horizontal edge
			else if ((ix==X1 || ix==X2) && iy>Y1) printf("\xBA"); // Vertical edge
			else printf(" ");
		}
	}
		// Draw all corners
		printf("%c[%d;%dH", ESC, Y1, X1); printf("\xC9");
		printf("%c[%d;%dH", ESC, Y1, X2); printf("\xBB");
		printf("%c[%d;%dH", ESC, Y2, X2); printf("\xBC");
		printf("%c[%d;%dH", ESC, Y2, X1); printf("\xC8");
}

void box(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2) {
	/*
	 * draw boxes in terminal
	 */
	for (int iy=y1; iy<=y2; iy++) { // Go through each row (y)
		printf("%c[%d;%dH", ESC, iy, x1); // go to left side in window
		for (int ix=x1; ix<=x2; ix++) { // // go through each column (x)
			if ((iy==y1 || iy==y2) && ix>x1) printf("\xC4"); // Horizontal edge
			else if ((ix==x1 || ix==x2) && iy>y1) printf("\xB3"); // Vertical edge
			else printf("%c[1C", ESC);
		}
	}
	// Draw all corners
	printf("%c[%d;%dH", ESC, y1, x1); printf("\xDA");
	printf("%c[%d;%dH", ESC, y1, x2); printf("\xBF");
	printf("%c[%d;%dH", ESC, y2, x2); printf("\xD9");
	printf("%c[%d;%dH", ESC, y2, x1); printf("\xC0");
}



