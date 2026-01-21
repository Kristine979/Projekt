/*
 * Help.c
 *
 *  Created on: 20 Jan 2026
 *      Author: Yurii
 */


#include "HelpScreen.h"


void PrintTextHelp(int x1, int y1, int x2, int y2, const char text[])
/*
 * Print text inside a box without overwriting borders, supports '\n'
 */
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


void help(ship_size_t *ship_size){
	/*
	 * Draw help screen
	 */
	printf("%c[%d;%dH   #   #  #####  #      #### ", ESC, 2, 2);
	printf("%c[%d;%dH   #   #  #      #      #   #", ESC, 3, 2);
	printf("%c[%d;%dH   #####  ####   #      #### ", ESC, 4, 2);
	printf("%c[%d;%dH   #   #  #      #      #    ", ESC, 5, 2);
	printf("%c[%d;%dH   #   #  #####  #####  #    ", ESC, 6, 2);


	PrintTextHelp(4, 7, 80, 28, "How to play the game:\n "
			"Game starts with the main menu. While we are in the main menu, \n"
			"we can start the game, see how many points we have earned,\n"
			"and access the help section where we are right now. \n"
			"When we press (Start), we have to choose the difficulty of the game.\n"
			"If we choose (Normal), we get the smallest, fastest, and most maneuverable ship.\n"
			"The (Hard) difficulty gives us a larger ship that is slower and less\n"
			"maneuverable, making it harder to dodge asteroids.\n"
			"The (Impossible) difficulty gives us a very large ship that is even\n"
			"slower than the previous ones, which makes dodging even more difficult.\n"
			"All ships have 3 lives, and they all shoot the same type of \n"
			"bullets. There are 8 levels in total. In each new level, there is one\n"
			"more alien enemy. In the first level there are 2 aliens, and in the \n"
			"last level there will be 9. The speed of asteroids also increases\n"
			"with each new level. If you complete all levels, you win and \n"
			"return to the menu. If you lose, you also return to the menu.\n");


	PrintTextHelp(4, 30, 80, 48, "Control:\n Controls are handled using the joystick, the SW1 and SW2 buttons, and the \n "
			"accelerometer.\n"
			"Pushing the joystick up moves up, and pushing it down moves down.\n"
			"Moving the joystick left or right moves left or right in the game while you\n"
			"are controlling the ship.\n"
			"The SW1 button works as OK in the menu and before the game starts.\n"
			"During gameplay it means shoot.\n"
			"The SW2 button pauses the game in any mode and shows a BOSS screen,\n"
			"pressing it again returns you to the game.\n"
			"If the ship takes damage, it will lose control. To restore control,\n"
			"you need to use the accelerometer on the microcontroller.\n"
			"Just shake the microcontroller.");



	PrintTextHelp(86, 7, 178, 28, "Asteroids and Aliens:\n"
			"Aliens are green objects. Hitting them once gives you 10 points. \n"
			"Hitting the aliens twice will kill them.\n"
			"Asteroids are grey objects. If you collide with an asteroid, you lose a life.\n"
			"Also, asteroids have their own gravitation field, so a bullet can change its flight path.\n");
	PrintTextHelp(86, 30, 178, 48, "Additional information:\n "
			"The ship can receive temporary buffs by collecting the following symbols:\n"
			"+ gives +1 life.\n"
			"* upgrades the bullets for 5 seconds: bullets pass through asteroids and are not affected\n"
			"by gravity.\n"
			"<< simply increases bullet speed for 5 seconds.\n"
			"\xB0 for 5 seconds, the ship fires 5 bullets in different directions.\n"
			"\n"
			"The life indicator can be seen on the microcontroller screen.");

	PrintText(4,50,20,52,0, "Back");
	alien_sprite(10, 170, 17);
	alien_sprite(10, 170, 22);
	asteroid_sprite(8, 150, 20);
	asteroid_sprite(8, 135, 16);
	asteroid_sprite(8, 120, 23);
	ship_3_sprite(110, 14, ship_size);
}
