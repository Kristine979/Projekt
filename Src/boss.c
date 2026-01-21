/*
 * boss.c
 *
 *  Created on: 15. jan. 2026
 *      Author: Bruger
 */



#include <stdio.h>
#include <stdint.h>
#include "ansi.h"
#include "menu.h"
#include "Help.h"


void boss(int y1, int y2) {
	int y = y1;
    while (y <= y2) {
        gotoxy(30, y);
        fgcolor(7);
        printf("%c[%d;%dH\xB3", ESC, y, 30);
        y++;
    }
    PrintText(4,3,20,5,1, "Documents");
    PrintText(4,7,26,9,1, "Accounting report");
    PrintText(4,10,26,12,1, "Perpetual motion m...");
    PrintText(4,13,26,15,1, "Bridge to Atlantis");
    PrintText(4,16,26,18,1, "Elixir of Immortality");
    PrintText(4,19,26,21,1, "Flight to Enceladus");
    PrintText(4,22,26,24,1, "DTU project");
    PrintText(4,25,26,27,1, "Order 66");
    fgcolor(15);
    PrintText(4,28,26,30,1, "Digital Electronics");
    PrintText(35,3,55,5,1, "Digital Electronics");
    fgcolor(7);
    PrintText(4,31,26,33,1, "Math");
    PrintText(4,34,26,36,1, "Electric circuits ");
    PrintText(4,37,26,39,1, "Computer programming");
    PrintText(4,40,26,42,1, "Programming Project");
    PrintText(4,43,26,45,1, "Exercises");
    PrintText(4,46,26,48,1, "Minecraft");
    PrintText(4,49,26,51,1, "Hytale");
    PrintTextHelp(32, 7, 174, 53,"VHDL code\n"
    		"architecture behavior2 of root191 is\n"
    		"begin\n"
    		"    with a(3 downto 1) select\n"
    		"y <= not a(0) when 001 \xB3 010 \xB3 100 \xB3 111,\n"
    		"         a(0) when others;\n"
    		"end architecture ");
}
