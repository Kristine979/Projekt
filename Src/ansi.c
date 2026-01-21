/*
 * ansi.c
 *
 *  Created on: 5. jan. 2026
 *      Author: Kristine
 */

#include "ansi.h"

#define ESC 0x1B

void fgcolor(uint8_t foreground) {
	//  is used to change the color of characters in the terminal.
/*  Value      foreground     Value     foreground
    ------------------------------------------------
      0        Black            8       Dark Gray
      1        Red              9       Light Red
      2        Green           10       Light Green
      3        Brown           11       Yellow
      4        Blue            12       Light Blue
      5        Purple          13       Light Purple
      6        Cyan            14       Light Cyan
      7        Light Gray      15       White
*/
  uint8_t type = 22;             // normal text
	if (foreground > 7) {
	  type = 1;                // bold text
		foreground -= 8;
	}
  printf("%c[%d;%dm", ESC, type, foreground+30);
}

void bgcolor(uint8_t background) {
	//  is used to change the color of characters in the terminal.
/* IMPORTANT:   When you first use this function you cannot get back to true white background in HyperTerminal.
   Why is that? Because ANSI does not support true white background (ANSI white is gray to most human eyes).
                The designers of HyperTerminal, however, preferred black text on white background, which is why
                the colors are initially like that, but when the background color is first changed there is no
 	              way comming back.
   Hint:        Use resetbgcolor(); clrscr(); to force HyperTerminal into gray text on black background.

    Value      Color
    ------------------
      0        Black
      1        Red
      2        Green
      3        Brown
      4        Blue
      5        Purple
      6        Cyan
      7        Gray
*/
  printf("%c[%dm", ESC, background+40);
}

void color(uint8_t foreground, uint8_t background) {
	// is used to change the colors of characters and the background in terminal.
// combination of fgcolor() and bgcolor() - uses less bandwidth
  uint8_t type = 22;             // normal text
	if (foreground > 7) {
	  type = 1;                // bold text
		foreground -= 8;
	}
  printf("%c[%d;%d;%dm", ESC, type, foreground+30, background+40);
}

void resetbgcolor() {
// gray on black text, no underline, no blink, no reverse
  printf("%c[m", ESC);
}

void clrscr() {
	// function that clears the terminal
	printf("%c[%d;%dH", ESC, 1, 1);
	printf("%c[J", ESC);
}
void clreol() {
	 //function that clears the rest of the current line
	printf("%c[K", ESC);
}
void gotoxy(int x, int y) {
	// function that takes two parameters (x and y) and moves the cursor to position (x,y)
	printf("%c[%d;%dH", ESC, y, x);
}
void underline(uint8_t on) {
	// function that takes one parameter to turn on/off underline
	if (on == 0) {
		printf("%c[24", ESC);
	}
	else
		printf("%c[04", ESC);
}
void blink(uint8_t on){
	// function that makes it blink
	if (on == 0) {
		printf("%c[25", ESC);
	}
	else
		printf("%c[05", ESC);
}

void inverse(uint8_t on) {
	// function that inverts it
	printf("%c[%d%c",ESC,7,'m');
}

