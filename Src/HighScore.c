/*
 * HighScore.c
 *
 *  Created on: 12. jan. 2026
 *      Author: Kristine
 */

#include "HighScore.h"

void update_hs(high_score_t *hs, uint16_t new_score) {
	/*
	 * Updates the current list of highscores after each played game
	 * Checks whether the new score should be on the board
	 */
	if (new_score > hs->h5) {
		if (new_score > hs->h4) {
			hs->h5 = hs->h4;
			if (new_score > hs->h3) {
				hs->h4 = hs->h3;
				if (new_score > hs->h2) {
					hs->h3 = hs->h2;
					if (new_score > hs->h1) {
						hs->h2 = hs->h1;
						hs->h1 = new_score;
							}
					else hs->h2 = new_score;
						}
				else hs->h3 = new_score;
					}
			else hs->h4 = new_score;
		}
		else hs->h5 = new_score;
	}
}

void hs_menu(high_score_t hs) {
	// draws the high score screen
	int x=2, y = 8;
	// title
	printf("%c[%d;%dH#   # ###  ###  #   #    ###  ###   ###  ###  ####", ESC, y-6, x);
	printf("%c[%d;%dH#   #  #  #     #   #   #    #   # #   # #  # #   ", ESC, y-5, x);
	printf("%c[%d;%dH#####  #  #  ## #####    ##  #     #   # ###  ####", ESC, y-4, x);
	printf("%c[%d;%dH#   #  #  #   # #   #      # #   # #   # #  # #   ", ESC, y-3, x);
	printf("%c[%d;%dH#   # ###  ###  #   #   ###   ###   ###  #  # ####", ESC, y-2, x);
	// high scores
	printf("%c[%d;%dH1.	%05ld", ESC, y, x, hs.h1);
	printf("%c[%d;%dH2.	%05ld", ESC, y+1, x, hs.h2);
	printf("%c[%d;%dH3.	%05ld", ESC, y+2, x, hs.h3);
	printf("%c[%d;%dH4.	%05ld", ESC, y+3, x, hs.h4);
	printf("%c[%d;%dH5.	%05ld", ESC, y+4, x, hs.h5);
	// back box
	PrintText(4,50,20,52,0, "Back");
}
