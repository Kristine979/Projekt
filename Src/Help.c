/*
 * Help.c
 *
 *  Created on: 16 Jan 2026
 *      Author: root
 */


#include "Help.h"

// Print text inside a box without overwriting borders, supports '\n'
void PrintTextHelp(int x1, int y1, int x2, int y2, const char text[])
{
    // 1) draw contour
    box(x1, y1, x2, y2);


    // 3) print INSIDE the box safely
    int cx   = (int)x1 + 1;
    int cy   = (int)y1 + 1;
    int maxx = (int)x2 - 1;
    int maxy = (int)y2 - 1;

    // if box too small, do nothing
    if (cx > maxx || cy > maxy) return;

    printf("%c[%d;%dH", ESC, cy, cx);

    for (const char *p = text; *p && cy <= maxy; p++) {

        if (*p == '\n') {
            cy++;
            cx = (int)x1 + 1;
            if (cy > maxy) break;
            printf("%c[%d;%dH", ESC, cy, cx);
            continue;
        }

        // wrap if we reached right inner edge
        if (cx > maxx) {
            cy++;
            cx = (int)x1 + 1;
            if (cy > maxy) break;
            printf("%c[%d;%dH", ESC, cy, cx);
        }

        putchar(*p);
        cx++;
    }
}


void help(){
	printf("%c[%d;%dH#   #  #####  #      #### ", ESC, 2, 2);
	printf("%c[%d;%dH#   #  #      #      #   #", ESC, 3, 2);
	printf("%c[%d;%dH#####  ####   #      #### ", ESC, 4, 2);
	printf("%c[%d;%dH#   #  #      #      #    ", ESC, 5, 2);
	printf("%c[%d;%dH#   #  #####  #####  #    ", ESC, 6, 2);

	PrintTextHelp(4, 7, 80, 28, "How to play the game:\n under development \n under development");
	PrintTextHelp(4, 30, 80, 48, "About something 1:\n under development \n under development");
	PrintTextHelp(86, 7, 178, 28, "About something 2:\n under development \n under development");
	PrintTextHelp(86, 30, 178, 48, "About something 3:\n under development \n under development");
	PrintText(4,50,20,52,0, "Back");
}
