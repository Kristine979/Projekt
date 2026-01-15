/*
 * Difficulty.c
 *
 *  Created on: Jan 15, 2026
 *      Author: root
 */

#include "Difficulty.h"
#include "menu.h"


void difficulty(){
	// print out "MENU" in big letters, one line at a time
	printf("%c[%d;%dH####  ##### ##### ##### ##### #####  #### #   # #     ##### #   #", ESC, 2, 2);
	printf("%c[%d;%dH#   #   #   #     #       #     #   #     #   # #       #   #   #", ESC, 3, 2);
	printf("%c[%d;%dH#   #   #   ####  ####    #     #   #     #   # #       #    ###", ESC, 4, 2);
	printf("%c[%d;%dH#   #   #   #     #       #     #   #     #   # #       #     #", ESC, 5, 2);
	printf("%c[%d;%dH####  ##### #     #     ##### #####  ####  ###  #####   #     #", ESC, 6, 2);
	//Print difficulty
	PrintText(4,7,20,9,0, "Normal");
	PrintText(4,10,20,12,1, "Hard");
	PrintText(4,13,20,15,1, "Impossible");
}
