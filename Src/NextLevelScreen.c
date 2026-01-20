/*
 * NextLevelScreen.c
 *
 *  Created on: 20 Jan 2026
 *      Author: root
 */


#include "NextLevelScreen.h"
#include "menu.h"

void NextLevelScreen(){
	int XL = 70;
	int YL = 10;
	printf("%c[%d;%dH#     # ####### #     # #######        #       ####### #     # ####### #      ", ESC, 2+YL, XL);
	printf("%c[%d;%dH##    # #        #   #     #           #       #       #     # #       #      ", ESC, 3+YL, XL);
	printf("%c[%d;%dH# #   # #         # #      #           #       #       #     # #       #      ", ESC, 4+YL, XL);
	printf("%c[%d;%dH#  #  # #####      #       #           #       #####    #   #  #####   #      ", ESC, 5+YL, XL);
	printf("%c[%d;%dH#   # # #         # #      #           #       #        #   #  #       #      ", ESC, 6+YL, XL);
	printf("%c[%d;%dH#    ## #        #   #     #           #       #         # #   #       #      ", ESC, 7+YL, XL);
	printf("%c[%d;%dH#     # ####### #     #    #           ####### #######    #    ####### #######", ESC, 8+YL, XL);

	PrintText(85, 47, 95, 49, 0, "Continue");
}
