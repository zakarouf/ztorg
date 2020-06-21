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


/*
-----------------------------------------------------
DEFAULT SIZE OF MINI MAP
----------------------------------------------------*/
#define MINI_MAP_X 7
#define MINI_MAP_Y 7
//-------------------------------------------------//

/*
-----------------------------------------------------
Value That'll be incremented in ray with each step
until wall is hit or depth limit is reached  
lower value = better precision but slower performence
----------------------------------------------------*/
#define RAY_DISTANCE_INCREMENT 0.1f
//-------------------------------------------------//



void render_scr_fin_ED (int px, int py, int scrX, int scrY) {

	clear();

	scrY -= 10;
	scrX = (scrX>>1) - 4;

	int sc_y = 0, sc_x = 0;

	int i = py - (int)(scrY>>1) -1, j;

	int end_i = py + (int)(scrY>>1) +1;
	int end_j = px + (int)(scrX>>1) +1;

	if (end_i >= mapED.Y) {end_i = mapED.Y; i = mapED.Y - scrY -1;}
	if (i < 0) {i = 0;
		if(scrY <= mapED.Y){
			end_i = scrY+1;
		}
	}

	sc_y++;

	for (; i < end_i; ++i)
	{

		j = px - (int)(scrX>>1) -1;
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

	j = px - (int)(scrX>>1) -1;
	if (end_j >= mapED.X) {end_j = mapED.X; j = mapED.X - scrX -1;}
	if (j < 0)  { j = 0;}
	for (; j < end_j; ++j)
	{
		printw("%i ", j%10);
	}
	addch('\n');

	j = px - (int)(scrX>>1) -1;
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

void render_scr_fin (int sc ,int sv ,int px, int py, int render_lim_X, int render_lim_Y) {
	
	int j, i = py - (int)(render_lim_Y>>1) -1;

	int end_i = py + (int)(render_lim_Y>>1) +1;
	int end_j = px + (int)(render_lim_X>>1) +1;

	if (end_i >= map1.Y) { end_i = map1.Y; i = map1.Y - render_lim_Y -1; }
	if (end_j >= map1.X) { end_j = map1.X; j = map1.X - render_lim_X -1; }
	
	if (i < 0) {i = 0;}

	for (; i < end_i; ++i)
	{

		j = px - (int)(render_lim_X>>1) -1;
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
	wclear(stdscr);

	move(0, 0);

	for (int x = 0; x < scrWIDTH; x++) 
	{
		float ray_angle = (playerA - FOV / 2.0f) + ((float)x / (float)scrWIDTH * FOV);

		float ray_distance = 0;
		int chech_if_hitwall = 0;

		bool out_of_bounds = 0;

		float p_eyeX = sinf(ray_angle);
		float p_eyeY = cosf(ray_angle);

		while (!chech_if_hitwall && ray_distance <= DEPTH && !out_of_bounds)
		{
			ray_distance += RAY_DISTANCE_INCREMENT;

			int testX = (int)(playerX+.5f + p_eyeX * ray_distance);
			int testY = (int)(playerY+.5f + p_eyeY * ray_distance);

			if(testX < 0 || testX >= map1.X || testY < 0 || testY >= map1.Y){

				out_of_bounds = true;
				ray_distance = DEPTH;
			}
			else {
				if(map1.world[testY][testX] == '#') {chech_if_hitwall = 1;}
				if(map1.world[testY][testX] == '*') {chech_if_hitwall = 2;}
			}	
		} // WHILE LOOP END

		int ceiling = (scrHEIGHT / 2) - scrHEIGHT / (ray_distance);
		int floor = scrHEIGHT - ceiling;

		int color_txt = 0;
		int shade = ' ';

		if 		(chech_if_hitwall == 1)	{color_txt = COLOR_WHITE;}
		else if (chech_if_hitwall == 2)	{color_txt = COLOR_YELLOW;}

		if(ray_distance >= DEPTH-4 ) {shade = '.';}
		if(ray_distance >= DEPTH-2)  {shade = ';';}
		if(ray_distance >= DEPTH-1 ) {shade = '#';}
		if(ray_distance == DEPTH)	 {shade = ' ';}




		for (int y = 0; y < scrHEIGHT; y++)
		{
			if(y > ceiling && y <= floor){
				if(!out_of_bounds && shade == ' '){
					attron(COLOR_PAIR(color_txt));
				}
				
				mvaddch(y, x, shade);

				if(!out_of_bounds && shade == ' '){
					attroff(COLOR_PAIR(color_txt));
				}
			}

		}

	}


	render_scr_fin(1 ,0 ,playerX, playerY , MINI_MAP_X, MINI_MAP_Y);
	mvprintw(0, 0, "X %2f Y %f A %2f", playerX, playerY, playerA);
}