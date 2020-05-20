/*
-----------------------------------------------------
SCREEN RENDERER SEGMENT
'fin' mode renders only surrounding of player (better
	for bigger maps.)

TODO: Fix error while rendering map with smaller scale
	  than SCREEN X/Y Dimention.
	  ADD Windows
----------------------------------------------------*/

#include "render.h"
#include "map.h"


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

	int end_i = py + (int)(SCREEN_Y/2) +1;
	int end_j = px + (int)(SCREEN_X/2) +1;

	if (end_i >= map1.Y) { end_i = map1.Y; i = map1.Y - SCREEN_Y -1; }
	if (end_j >= map1.X) { end_j = map1.X; j = map1.X - SCREEN_X -1; }
	if (i < 0) {i = 0;}

	for (; i < end_i; ++i)
	{

		j = px - (int)(SCREEN_X/2) -1;
		if (j < 0)  { j = 0;}
		

		move(sc, sv);
		for (; j < end_j; ++j)
		{

			addch(map1.world[i][j]);
			addch(' ');
		}
		sc++;
	}
}

void render_scr_fin_ED (int px, int py) {
	clear();
	int sc_y = 0, sc_x = 0;

	int i = py - (int)(SCREEN_Y/2) -1, j;

	int end_i = py + (int)(SCREEN_Y/2) +1;
	int end_j = px + (int)(SCREEN_X/2) +1;

	if (end_i >= mapED.Y) {end_i = mapED.Y; i = mapED.Y - SCREEN_Y -1;}
	if (i < 0) {i = 0;
		if(SCREEN_Y <= mapED.Y){
			end_i = SCREEN_Y+1;
		}
	}

	sc_y++;

	for (; i < end_i; ++i)
	{

		j = px - (int)(SCREEN_X/2) -1;
		if (end_j >= mapED.X) {end_j = mapED.X; j = mapED.X - SCREEN_X -1;}
		if (j < 0) {j = 0;
			if(SCREEN_X <= mapED.X){
				end_j = SCREEN_X+1;
			}
		}

		move(sc_y, sc_x);
		for (; j < end_j; ++j)
		{	
			if (mask[i][j] != ' ')
			{
				printw("%c ", mask[i][j]);
			}
			else {
				printw("%c ",mapED.world[i][j]); 		//plot map
			}
			
		}
		printw("\b| %d", i);
		sc_y++;
	}
	addch('\n');

	j = px - (int)(SCREEN_X/2) -1;
	if (end_j >= mapED.X) {end_j = mapED.X; j = mapED.X - SCREEN_X -1;}
	if (j < 0)  { j = 0;}
	for (; j < end_j; ++j)
	{
		printw("%i ", j%10);
	}
	addch('\n');

	j = px - (int)(SCREEN_X/2) -1;
	if (end_j >= mapED.X) {end_j = mapED.X; j = mapED.X - SCREEN_X -1;}
	if (j < 0)  { j = 0;}
	addch(' ');
	for (; j < end_j; j++)
	{
		if (j%10==0)
		{
			attron(COLOR_PAIR(1));
			printw("\b%d", j/10);
			attroff(COLOR_PAIR(1));
		};
		addch(' ');addch(' ');
	}
}
/*
void render_scr_win_ED (int px, int py) {

	WINDOW * scr_ren = newwin(SCREEN_Y+1, SCREEN_X*2 +1, 0, 0);
	refresh();
	box(scr_ren, 0, 0);
	wrefresh(scr_ren);

	int sc_y = 1, sc_x = 1;

	int i = py - (int)(SCREEN_Y/2) -1, j;

	int end_i = py + (int)(SCREEN_Y/2) +1;
	int end_j = px + (int)(SCREEN_X/2) +1;

	if (end_i >= mapED.Y) {end_i = mapED.Y; i = mapED.Y - SCREEN_Y -1;}
	if (end_j >= mapED.X) {end_j = mapED.X; j = mapED.X - SCREEN_X -1;}
	if (i < 0) {i = 0;}

	for (; i < end_i; ++i)
	{

		j = px - (int)(SCREEN_X/2) -1; sc_x=1;
		for (; j < end_j; ++j)
		{
			mvwprintw(scr_ren, sc_y, sc_x, "%c ",mapED.world[i][j]); 		//plot map
			sc_x++;
		}
		sc_y++;
	}
	wrefresh(scr_ren);
	//mvwaddch(scr_ren, , int, const chtype)

}
*/