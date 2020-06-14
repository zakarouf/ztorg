/*
-----------------------------------------------------
SCREEN RENDERER SEGMENT
'fin' mode renders only surrounding of player (better
	for bigger maps.)

TODO: Fix error while rendering map with smaller scale
	  than SCREEN X/Y Dimention.
	  ADD Windows
----------------------------------------------------*/

#include <math.h>
#include "render.h"
#include "map.h"
#include "stdlibra.h"

#define MINI_MAP_X DEPTH+2
#define MINI_MAP_Y DEPTH+2

void render_scr_fin_ED (int px, int py, int scrX, int scrY) {

	clear();

	scrY = scrY * 3/4;
	scrX = (scrX/2) - (scrX/10);

	int sc_y = 0, sc_x = 0;

	int i = py - (int)(scrY/2) -1, j;

	int end_i = py + (int)(scrY/2) +1;
	int end_j = px + (int)(scrX/2) +1;

	if (end_i >= mapED.Y) {end_i = mapED.Y; i = mapED.Y - scrY -1;}
	if (i < 0) {i = 0;
		if(scrY <= mapED.Y){
			end_i = scrY+1;
		}
	}

	sc_y++;

	for (; i < end_i; ++i)
	{

		j = px - (int)(scrX/2) -1;
		if (end_j >= mapED.X) {end_j = mapED.X; j = mapED.X - scrX -1;}
		if (j < 0) {j = 0;
			if(scrX <= mapED.X){
				end_j = scrX+1;
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

	j = px - (int)(scrX/2) -1;
	if (end_j >= mapED.X) {end_j = mapED.X; j = mapED.X - scrX -1;}
	if (j < 0)  { j = 0;}
	for (; j < end_j; ++j)
	{
		printw("%i ", j%10);
	}
	addch('\n');

	j = px - (int)(scrX/2) -1;
	if (end_j >= mapED.X) {end_j = mapED.X; j = mapED.X - scrX -1;}
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

void render_scr_fin (int px, int py) {
	
	int sc = 1, sv = 0;


	int j, i = py - (int)(MINI_MAP_Y/2) -1;

	int end_i = py + (int)(MINI_MAP_Y/2) +1;
	int end_j = px + (int)(MINI_MAP_X/2) +1;

	if (end_i >= map1.Y) { end_i = map1.Y; i = map1.Y - MINI_MAP_Y -1; }
	if (end_j >= map1.X) { end_j = map1.X; j = map1.X - MINI_MAP_X -1; }
	
	if (i < 0) {i = 0;}

	for (; i < end_i; ++i)
	{

		j = px - (int)(MINI_MAP_X/2) -1;
		if (j < 0)  { j = 0;}
		

		move(sc, sv);
		for (; j < end_j; ++j)
		{

			addch(map1.world[i][j]);
			if(j == px && i == py ){
				addch('\b');
				addch('@');
			}
		}
		sc++;
	}
	
}

void raycasting_test (float playerX, float playerY, float playerA, int scrWIDTH,int scrHEIGHT) {
	clear();

	move(0, 0);

	for (int x = 0; x < scrWIDTH; x++) 
	{
		float ray_angle = (playerA - FOV / 2.0f) + ((float)x / (float)scrWIDTH * FOV);

		float ray_distance = 0;
		int chech_if_hitwall = 0;

		int out_of_bounds = 0;

		float p_eyeX = sinf(ray_angle);
		float p_eyeY = cosf(ray_angle);

		while (!chech_if_hitwall && ray_distance < DEPTH && !out_of_bounds)
		{
			ray_distance += 0.1f;

			int testX = (int)(playerX + p_eyeX * ray_distance);
			int testY = (int)(playerY + p_eyeY * ray_distance);

			if(testX < 0 || testX >= map1.X || testY < 0 || testY >= map1.Y){

				chech_if_hitwall = 1;
				//out_of_bounds = 1;
				ray_distance = DEPTH;
			}
			else {
				if(map1.world[testY][testX] == '#') {chech_if_hitwall = 1;}
				if(map1.world[testY][testX] == '*') {chech_if_hitwall = 2;}
			}	
		} // WHILE LOOP END

		int ceiling = (scrHEIGHT / 2) - scrHEIGHT / (ray_distance);
		int floor = scrHEIGHT - ceiling;

		int shade;

		if(chech_if_hitwall == 1){
			shade = COLOR_WHITE;
		}
		else {shade = COLOR_YELLOW;}

		for (int y = 0; y < scrHEIGHT; y++)
		{
			if(y > ceiling && y <= floor){
				attron(COLOR_PAIR(shade));
				mvaddch(y, x, ' ');
				attroff(COLOR_PAIR(shade));

			}
		}

	}


	render_scr_fin(playerX, playerY);
	mvprintw(0, 0, "X %2f Y %f A %2f", playerX, playerY, playerA);
}
