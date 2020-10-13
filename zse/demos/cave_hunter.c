
#include "../zse.h"
#include "../r_curses/r_sprites.h"

static int ren(WINDOW *win, SPRITES_t *spr, TILESET_t *ts, ST_WORLD_t * map, ENTT_t *p)
{

	const int screensizeX = getmaxx(win);
	const int screensizeY = getmaxy(win);

	int cursor_y = 0, cursor_x = 0;

	int i = p->Y - (int)(screensizeY>>1) -1, j;

	int end_i = p->Y + (int)(screensizeY>>1) +1;
	int end_j = p->X + (int)(screensizeX>>1) +1;

	if (end_i >= map->Ysize) {end_i = map->Ysize; i = map->Ysize - screensizeY -1;}
	if (i < 0) {
		i = 0;
		if(screensizeY <= map->Ysize){
			end_i = screensizeY+1;
		}
	}

	for (; i < end_i; ++i)
	{

		j = p->X - (int)(screensizeX>>1) -1;
		if (end_j >= map->Xsize) {end_j = map->Xsize; j = map->Xsize - screensizeX -1;}
		if (j < 0) {j = 0;
			if(screensizeX <= map->Xsize){
				end_j = screensizeX+1;
			}
		}

		for (; j < end_j; ++j)
		{
			if (map->chunk[getindex3d(j, i, 0, zse_mapx(map), zse_mapy(map))] == 1)
			{
				mvwaddch(win, cursor_y/4, cursor_x/4, '#');
				//zse_render_sprite(stdscr, cursor_x, cursor_y, spr, 0);	
			}

			cursor_x += ts->tiletexsize;
		}
		cursor_y += ts->tiletexsize;
	}

	return 0;
}

int demo_cave_hunter ()
{
	ENTT_t *player = init_ENTT_t (JACK);
	player->Z = 0.0f;
	player->X = 1.0f;
	player->Y = 1.0f;

	char t[ZSE_MAX_FILENAME_SIZE];
	ST_WORLD_t *map = zse_map_load_st("ch_t", t);
	TILESET_t ts = zse_tileset_get(t);

	enum
	{
		P1,
		BLOC,
	};

	SPRITES_t spr[2];
	spr[P1] = zse_sprites_sin_load("p1");
	spr[BLOC] = zse_sprites_sin_load("bloc");

	nodelay(stdscr, TRUE);
	char state = 1;

	while(TRUE)
	{
		wclear(stdscr);
		switch(getch())
		{
			case 'a':
				player->X--;
				state = 1;
				break;
			case 'd':
				player->X++;
				state = 2;
				break;
			case 'w':
				player->Y--;
				break;
			case 's':
				player->Y++;
				break;
			
			case '`':
				return 0;
				break;

			default:
				break;

		}
		zse_render_sprite(stdscr, 0, 0, &spr[P1], 0);
		zse_render_sprite(stdscr, 0, 0, &spr[P1], state);
		

		//wclear(stdscr);
		wrefresh(stdscr);
		//ren(stdscr, &spr[BLOC], &ts, map, player);
		wrefresh(stdscr);
	}
	
	return 0;
}