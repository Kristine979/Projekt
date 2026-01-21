/*
 * NextLevelScreen.c
 *
 *  Created on: 20 Jan 2026
 *      Author: Yurii
 */


#include "NextLevelScreen.h"

void NextLevelScreen(){
	/*
	 * Draw next level screen
	 */
	int XL = 50;
	int YL = 15;
	printf("%c[%d;%dH#     # ####### #     # #######        #       ####### #     # ####### #      ", ESC, 2+YL, XL);
	printf("%c[%d;%dH##    # #        #   #     #           #       #       #     # #       #      ", ESC, 3+YL, XL);
	printf("%c[%d;%dH# #   # #         # #      #           #       #       #     # #       #      ", ESC, 4+YL, XL);
	printf("%c[%d;%dH#  #  # #####      #       #           #       #####    #   #  #####   #      ", ESC, 5+YL, XL);
	printf("%c[%d;%dH#   # # #         # #      #           #       #        #   #  #       #      ", ESC, 6+YL, XL);
	printf("%c[%d;%dH#    ## #        #   #     #           #       #         # #   #       #      ", ESC, 7+YL, XL);
	printf("%c[%d;%dH#     # ####### #     #    #           ####### #######    #    ####### #######", ESC, 8+YL, XL);

}
