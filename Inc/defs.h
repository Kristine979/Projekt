/*
 * defs.h
 *
 *  Created on: 12. jan. 2026
 *      Author: Bruger
 */

#ifndef DEFS_H_
#define DEFS_H_
#define ESC 0x1B
#define X1 1 // top left x-coordinate of the screen
#define Y1 1 // top left y-coordinate of the screen
#define X2 180 // bottom right x-coordinate of the screen
#define Y2 54 // bottom right y-coordinate of the screen
#define MENU 0
#define DIFF 1
#define HS 2
#define HELP 3
#define GAME 4
#define BOSS 5
#define GAMEOVER 6
#define NEXTLEVEL 7
#define NOPUSH 0
#define WHITE 1
#define RED 2
#define ON 1
#define OFF 0
#define MAXBULLETS 15
#include "stm32f30x_conf.h" // STM32 config
#include "30010_io.h" // Input/output library for this course
#include <stdlib.h>


#endif /* DEFS_H_ */
