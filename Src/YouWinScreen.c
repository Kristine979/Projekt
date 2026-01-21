/*
 * YouWinScreen.c
 *
 *  Created on: 20 Jan 2026
 *      Author: Yurii
 */

#include "YouWinScreen.h"

void youwin(){
	/*
	 * Draw the win screen
	 */
	int XW = 50;
	int YW = 10;
	printf("%c[%d;%dH                                        ###################                                         ", ESC, 2+YW, XW);
	printf("%c[%d;%dH                                        #######+########-+#                                         ", ESC, 3+YW, XW);
	printf("%c[%d;%dH                                        ##+###+#########-+#                                         ", ESC, 4+YW, XW);
	printf("%c[%d;%dH                                 #########+###+#########-+########                                  ", ESC, 5+YW, XW);
	printf("%c[%d;%dH                                 #########+###++########-+########                                  ", ESC, 6+YW, XW);
	printf("%c[%d;%dH                                 ####   ######+++++#####-+#    ###                                  ", ESC, 7+YW, XW);
	printf("%c[%d;%dH                                  #####-##+##+####+#####-+#######                                   ", ESC, 8+YW, XW);
	printf("%c[%d;%dH                                     ########+####+############                                     ", ESC, 9+YW, XW);
	printf("%c[%d;%dH                                           #############                                            ", ESC, 10+YW, XW);
	printf("%c[%d;%dH                                           #############                                            ", ESC, 11+YW, XW);
	printf("%c[%d;%dH                                              #######                                               ", ESC, 12+YW, XW);
	printf("%c[%d;%dH                                              #######                                               ", ESC, 13+YW, XW);
	printf("%c[%d;%dH                                              #######                                               ", ESC, 14+YW, XW);
	printf("%c[%d;%dH                                           #############                                            ", ESC, 15+YW, XW);
	printf("%c[%d;%dH                                           #############                                            ", ESC, 16+YW, XW);
	printf("%c[%d;%dH####   ###     #######      ###    ####           ###     ###   ##########   ###     ###   ###   ", ESC, 20+YW, XW);
	printf("%c[%d;%dH####   ###   ###     ###    ###    ####           ###     ###      ####      #####   ###   ###   ", ESC, 21+YW, XW);
	printf("%c[%d;%dH####   ###   ###     ###    ###    ####           ### ##  ###      ####      ######  ###   ###   ", ESC, 22+YW, XW);
	printf("%c[%d;%dH  ######     ###     ###    ###    ####           ###########      ####      ###########   ###   ", ESC, 23+YW, XW);
	printf("%c[%d;%dH    ###      ###     ###    ###    ####           ###########      ####      ###  ######   ###   ", ESC, 24+YW, XW);
	printf("%c[%d;%dH    ###      ###########    ###########           ####  #####   ##########   ###    ####         ", ESC, 25+YW, XW);
	printf("%c[%d;%dH    ###        #######        #######             ##       ##   ##########   ###     ###   ***   ", ESC, 26+YW, XW);
	PrintText(85, 47, 105, 49, 0, "Return to Main Menu");
}
