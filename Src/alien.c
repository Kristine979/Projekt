/*
 * alien.c
 *
 *  Created on: 14. jan. 2026
 *      Author: carol
 */

#include "alien.h"
#include "sprites.h"
#include "clock.h"

struct alien_info {
	//char alive;
	int sec;
	int min;
	int hour;
	int x;
	int y;

};


struct alien_info arr[4];

void spawn(int number, int x, int y){
	arr[number].x = x + 145;
	arr[number].y = y + 5;
	alien_sprite(10, 145+x, 5+y);
	int temp_sec = t.s + 3;
	if (temp_sec > 59){
		temp_sec -= 60;
	}
	arr[number].sec = temp_sec;
}

void update_alien(int number){
	if (t.s == arr[number].sec){
		asteroid_sprite(8, arr[number].x - 8, arr[number].y-1);
	}
}


