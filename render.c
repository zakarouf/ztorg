#include "render.h"
#include "map.h"
#include <ncurses.h>

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