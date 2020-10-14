#include "zse_all.h"

void zse_r_render_world_raycast (WINDOW *win, ENTT_t *player, ST_WORLD_t *map, TILE_t *tile)
{
	wclear(win);

	int color_txt = 1;
	wmove(win ,0, 0);

	for (int x = 0; x < getmaxx(win); x++) 
	{
		float ray_angle = (player->A - FOV / 2.0f) + ((float)x / (float)getmaxx(win) * FOV);

		float ray_distance = 0;
		int chech_if_hitwall = 0;

		char out_of_bounds = 0;

		float p_eyeX = sinf(ray_angle);
		float p_eyeY = cosf(ray_angle);

		while (!chech_if_hitwall && ray_distance <= DEPTH && !out_of_bounds)
		{
			ray_distance += RAY_DISTANCE_INCREMENT;

			int testX = (int)(player->X+0.5f + p_eyeX * ray_distance);
			int testY = (int)(player->Y+0.5f + p_eyeY * ray_distance);

			if(testX < 0 || testX >= map->Xsize || testY < 0 || testY >= map->Ysize){

				out_of_bounds = TRUE;
				ray_distance = DEPTH;
			}
			else {
				if((tile[map->chunk[getindex3d(testX, testY, (int)player->Z, map->Xsize, map->Ysize)]].attr & TILE_ISBLOC) && !(tile[map->chunk[getindex3d(testX, testY, (int)player->Z, map->Xsize, map->Ysize)]].attr & TILE_ISINVI)) 
				{
					chech_if_hitwall = 1;
					color_txt = tile[map->chunk[getindex3d(testX, testY, (int)player->Z, map->Xsize, map->Ysize)]].coloc;
				}
			}	
		} // WHILE LOOP END

		int ceiling = (getmaxy(win) / 2) - getmaxy(win) / (ray_distance);
		int floor = getmaxy(win) - ceiling;


		int shade = ' ';

		if(ray_distance >= DEPTH-4 ) {shade = '.';}
		if(ray_distance >= DEPTH-2)  {shade = ';';}
		if(ray_distance >= DEPTH-1 ) {shade = '#';}
		if(ray_distance == DEPTH)	 {shade = ' ';}


		for (int y = 0; y < getmaxy(win); y++)
		{
			if(y > ceiling && y <= floor){
				if(!out_of_bounds && shade == ' ')
				{
					attron(COLOR_PAIR(color_txt));
				}
				
				mvwaddch(win ,y, x, shade);

				if(!out_of_bounds && shade == ' ')
				{
					attrset(A_NORMAL);
				}
			}

		}

	}


	//render_scr_fin(1 ,0 ,playerX, playerY , MINI_MAP_X, MINI_MAP_Y);
	mvprintw(0, 0, "X %2f Y %f A %2f", player->X, player->Y, player->A);
	wrefresh(stdscr);
}