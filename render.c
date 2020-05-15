#include "render.h"
#include "map.h"
#include <ncurses.h>

#define SCREEN_X 21
#define SCREEN_Y 21

void render_scr_ED (int x, int y) {
	clear();
	for (int i = 0; i < mapED.Y; ++i){

		move(i+y, x);addch('|');

		for (int j = 0; j < mapED.X; ++j){

			addch(mapED.world[i][j]);
			addch(' ');
		}
		printw("\b| %d", i);
	}	
}

void render_scr () {
	clear();
	for (int i = 0; i < map1.Y; ++i)
	{	
		move(i, 0);
		for (int j = 0; j < map1.X; ++j)
		{
			addch(map1.world[i][j]);
			addch(' ');
		}
	}
}


void render_scr_fin (int px, int py) {
	clear();
	int sc = 0, sv = 0;
	int i = py - (int)(SCREEN_Y/2) -1, j;
	//if (j < 0){j = 0;}
	int ei = py + (int)(SCREEN_Y/2) +1;
	int ej = px + (int)(SCREEN_X/2) +1;

	if (i < 0) {i = 0; ei = SCREEN_Y +1;}
	if (ei >= map1.Y) { ei = map1.Y; i = map1.Y - SCREEN_Y -1; }

	for (; i < ei; ++i)
	{

		j = px - (int)(SCREEN_X/2) -1;
		if (j < 0)  { j = 0;  ej = SCREEN_X +1;}
		if (ej >= map1.X) { ej = map1.X; j = map1.X - SCREEN_X -1; }

		move(sc, sv);
		for (; j < ej; ++j)
		{

			addch(map1.world[i][j]);
			addch(' ');
		}
		sc++;
	}
}

void render_scr_fin_ED (int px, int py) {
	clear();
	int sc = 0, sv = 0;
	int i = py - (int)(SCREEN_Y/2) -1, j;
	//if (j < 0){j = 0;}
	int ei = py + (int)(SCREEN_Y/2) +1;
	int ej = px + (int)(SCREEN_X/2) +1;

	if (i < 0) {i = 0; ei = SCREEN_Y + 1;}
	if (ei >= mapED.Y) { ei = mapED.Y; i = mapED.Y - SCREEN_Y -1; }

	for (; i < ei; ++i)
	{

		j = px - (int)(SCREEN_X/2) -1;
		if (j < 0)  { j = 0;  ej = SCREEN_X +1;}
		if (ej >= mapED.X) { ej = mapED.X; j = mapED.X - SCREEN_X -1; }

		move(sc, sv);
		for (; j < ej; ++j)
		{

			addch(mapED.world[i][j]);
			addch(' ');
		}
		printw("\b| %d", i);
		sc++;
	}
}