#include "r_lib.h"
#include "t_def.h"

/*
-----------------------------------------------------
SCREEN RENDERER SEGMENT
'2D_fin' mode renders only surrounding of player (better
	for bigger maps.)

TODO: Fix error while rendering map with smaller scale
	  than SCREEN X/Y Dimention.
	  ADD Windows
----------------------------------------------------*/


void r_map_2D_win (WINDOW *mini_map, PLAYER *p, MAP *m, TILE *tile, int lookdirY, int lookdirX)
{
	wclear(mini_map);
	box(mini_map, 0, 0);
	int render_lim_X, render_lim_Y;
	getmaxyx(mini_map, render_lim_Y, render_lim_X);

	render_lim_Y-=3;
	render_lim_X-=3;
	int j, i = p->Y - (int)(render_lim_Y>>1) -1;

	int end_i = p->Y + (int)(render_lim_Y>>1) +1;
	int end_j = p->X + (int)(render_lim_X>>1) +1;

	if (end_i >= m->Y) { end_i = m->Y; i = m->Y - render_lim_Y -1; }
	if (end_j >= m->X) { end_j = m->X; j = m->X - render_lim_X -1; }

	if (i < 0) {i = 0;}
	
	int x = 1, y = 1;

	for (; i < end_i; ++i)
	{

		j = p->X - (int)(render_lim_X>>1) -1;
		if (j < 0)  { j = 0;}
		

		wmove(mini_map ,y, x);
		
		for (; j < end_j; ++j)
		{

			waddch(mini_map, tile[m->world[i][j]].symb);
			if(j == (int)p->X && i == (int)p->Y ){
				waddch(mini_map,'\b');
				waddch(mini_map,'@');
				mvaddch(y + lookdirY+2, x + lookdirX, 'o');
			}
			x++;
		}
		x = 1;
		y++;
	}
	wrefresh(mini_map);
	mvprintw(1, 10, " %d %d", lookdirY, lookdirX);

}


void r_editor_main (EDITOR *editor, MAP *map, TILE *tile,int scrX, int scrY) {

	clear();

	int sc_y = 0, sc_x = 0;

	int i = editor->Y - (int)(scrY>>1) -1, j;

	int end_i = editor->Y + (int)(scrY>>1) +1;
	int end_j = editor->X + (int)(scrX>>1) +1;

	if (end_i >= map->Y) {end_i = map->Y; i = map->Y - scrY -1;}
	if (i < 0) {i = 0;
		if(scrY <= map->Y){
			end_i = scrY+1;
		}
	}

	sc_y++;

	for (; i < end_i; ++i)
	{

		j = editor->X - (int)(scrX>>1) -1;
		if (end_j >= map->X) {end_j = map->X; j = map->X - scrX -1;}
		if (j < 0) {j = 0;
			if(scrX <= map->X){
				end_j = scrX+1;
			}
		}

		move(sc_y, sc_x);


		for (; j < end_j; ++j)
		{
			addch(tile[map->world[i][j]].symb);
			if (i == editor->Y && j == editor->X)
			{
				addch('\b');
				addch('@');
			}
			//addch(' ');
		}
		printw("| %d", i);
		sc_y++;
	}
	addch('\n');


/*
	j = editor->X - (int)(scrX>>1) -1;
	if (end_j >= map->X) {end_j = map->X; j = map->X - scrX -1;}
	if (j < 0)  { j = 0;}
	for (; j < end_j; ++j)
	{
		printw("%i ", j%10);
	}
	addch('\n');


	j = editor->X - (int)(scrX>>1) -1;
	if (end_j >= map->X) {end_j = map->X; j = map->X - scrX -1;}
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
*/
}



void r_render_world_raycast (PLAYER *player, MAP *map, TILE *tile)
{
	wclear(stdscr);

	int scrWIDTH, scrHEIGHT;
	getmaxyx(stdscr, scrHEIGHT, scrWIDTH);

	int color_txt = 1;
	move(0, 0);

	for (int x = 0; x < scrWIDTH; x++) 
	{
		float ray_angle = (player->A - FOV / 2.0f) + ((float)x / (float)scrWIDTH * FOV);

		float ray_distance = 0;
		int chech_if_hitwall = 0;

		bool out_of_bounds = 0;

		float p_eyeX = sinf(ray_angle);
		float p_eyeY = cosf(ray_angle);

		while (!chech_if_hitwall && ray_distance <= DEPTH && !out_of_bounds)
		{
			ray_distance += RAY_DISTANCE_INCREMENT;

			int testX = (int)(player->X+.5f + p_eyeX * ray_distance);
			int testY = (int)(player->Y+.5f + p_eyeY * ray_distance);

			if(testX < 0 || testX >= map->X || testY < 0 || testY >= map->Y){

				out_of_bounds = true;
				ray_distance = DEPTH;
			}
			else {
				if((tile[map->world[testY][testX]].attr & TILE_ISWALL) && !(tile[map->world[testY][testX]].attr & TILE_ISINVI)) 
				{
					chech_if_hitwall = 1;
					color_txt = tile[map->world[testY][testX]].coloc;
				}
			}	
		} // WHILE LOOP END

		int ceiling = (scrHEIGHT / 2) - scrHEIGHT / (ray_distance);
		int floor = scrHEIGHT - ceiling;


		int shade = ' ';

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


	//render_scr_fin(1 ,0 ,playerX, playerY , MINI_MAP_X, MINI_MAP_Y);
	mvprintw(0, 0, "X %2f Y %f A %2f", player->X, player->Y, player->A);
	wrefresh(stdscr);
}
