/*
 * menu.c
 *
 *  Created on: 12. jan. 2026
 *      Author: Kristine
 */

#include "menu.h"

// hardcoded arrow positions
#define ARROW_X     3
#define START_Y     8
#define Y_SPACING   3
#define ARROW_CNT   3

//ADC joystick
#define ADC_CENTER    2048
#define ADC_DEADZONE  300

void PrintText(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t num, char text[]) {
	/*
	 * Print out given text in a box
	 */
		box(x1,y1,x2,y2);
		printf("%c[%d;%dH%s", ESC, y1+1, x1+1, text);
		if (num == 0) {
			printf("%c[%d;%dH\x3E", ESC, y1+1, x1-1);
		}
}

void menu() {
	/*
	 * print out "MENU" in big letters, one line at a time
	 */
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

static void cursorMove(uint8_t x, uint8_t y){
	/*
	 * Move cursor
	 */
    printf("\033[%d;%dH", y, x);
}


static uint8_t arrowY(uint8_t index){
	/*
	 * Calculate Y from index
	 */
    return START_Y + (index * Y_SPACING);
}

static void drawArrow(uint8_t index){
	/*
	 * Draw arrows using 0x3E
	 */
    cursorMove(ARROW_X, arrowY(index));
    printf("%c", 0x3E);
}

void Arrow_Clear(ArrowState *arrow){
	/*
	 * Clear arrow from screen
	 */
    cursorMove(ARROW_X, arrowY(arrow->index));
    printf(" ");
}


void Arrow_init(ArrowState *arrow){
	/*
	 * Initialize arrow
	 */
    arrow->index   = 0;
    arrow->lastDir = 0;
    drawArrow(arrow->index);
}

void Arrow_Update(ArrowState *arrow, int32_t adcValue){
	/*
	 * Update the arrows position, and draw a new one
	 */
    int8_t dir;

    // ADC → retning
    if (adcValue < (2048 - 300))
        dir = 1;       // NED
    else if (adcValue > (2048 + 300))
        dir = -1;      // OP
    else
        dir = 0;       // NEUTRAL

    // Move ONLY when leaving neutral
    if (dir != 0 && arrow->lastDir == 0)
    {
        // Erase the old arrow
        printf("\033[%d;%dH ", 8 + arrow->index * 3, 3);

        if (dir > 0 && arrow->index < 2)
            arrow->index++;
        else if (dir < 0 && arrow->index > 0)
            arrow->index--;

        // Draw new arrow
        printf("\033[%d;%dH%c", 8 + arrow->index * 3, 3, 0x3E);
    }

    // Save the last direction
    arrow->lastDir = dir;
}
