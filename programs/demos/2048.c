#include "demo.h"

static int _checkifall_true(char c[], int size)
{
	for (int i = 0; i < size; ++i)
	{
		if (!c[i])
		{
			return FALSE;
		}
	}
	return TRUE;
}

static int _d_2048_getrandom(ST_WORLD_t* map, int range)
{
	char checkarr[zse_mapx(map) * zse_mapy(map) * zse_mapz(map)];

	while(TRUE)
	{
		int ran = random()% (zse_mapx(map) * zse_mapy(map) * zse_mapz(map));

		if (checkarr[ran] == TRUE)
		{
			if (_checkifall_true(checkarr, zse_mapx(map) * zse_mapy(map) * zse_mapz(map)) == TRUE)
			{
				return 1;
			}
			else
			{
				continue;
			}
		}
		else
		{
			if (map->chunk[ran] == 0)
			{
				map->chunk[ran] = random()% range;
				return 0;
			}
		}

		checkarr[ran] = TRUE;
	}

	
	return 1;
}
/*
static int _d_2048_draw_boxline(WINDOW*win, int x, int y, int x1, int y1, int tilesize)
{

	for (int i = 0; i < x1 * tilesize; ++i)
	{
		mvwaddch(win, 0, i+x ,'-');

		if (i % tilesize == 0)
		{
			mvwaddch(win, y, i+x+1 , '+');
		}

	}

	return 0;
}
*/

static int _d_2048_draw(WINDOW*win, int x, int y, ST_WORLD_t *map)
{
	//int tilesize = 1;

	//_d_2048_draw_boxline(win, x, y, zse_mapx(map), zse_mapy(map), tilesize);
	

	for (int i = 0; i < zse_mapy(map); ++i)
	{
		for (int j = 0; j < zse_mapx(map); ++j)
		{
			mvwprintw(win, (i+y) *2, (j+x) *2, "%d " , map->chunk[zse_xyz3Dto1D(j, i, 0, zse_mapx(map), zse_mapx(map))]);
		}
	}

	//_d_2048_draw_boxline(win, x, zse_mapy(map)*tilesize, zse_mapx(map), zse_mapy(map), tilesize);

	return 0;
}

static int _d_2048_logic_add(ST_WORLD_t* map, char key)
{

	if (key == 'w')
	{
		for (int x = 0; x < zse_mapx(map); ++x)
		{
			for (int y = zse_mapy(map) - 1; y < 0; y -= 1)
			{
				if (map->chunk[zse_xyz3Dto1D(x, 3, 0, zse_mapx(map), zse_mapy(map))] == map->chunk[zse_xyz3Dto1D(x, 2, 0, zse_mapx(map), zse_mapy(map))])
				{
					map->chunk[zse_xyz3Dto1D(x, 2, 0, zse_mapx(map), zse_mapy(map))] = map->chunk[zse_xyz3Dto1D(x, 3, 0, zse_mapx(map), zse_mapy(map))] + map->chunk[zse_xyz3Dto1D(x, 2, 0, zse_mapx(map), zse_mapy(map))];
					map->chunk[zse_xyz3Dto1D(x, 3, 0, zse_mapx(map), zse_mapy(map))] = 0;
				}
			}
		}
	}

	else if (key == 's')
	{
		for (int x = 0; x < zse_mapx(map); ++x)
		{
			for (int y = 0; y < zse_mapy(map)-1; ++y)
			{
				if (map->chunk[zse_xyz3Dto1D(x, y+1, 0, zse_mapx(map), zse_mapy(map))] == map->chunk[zse_xyz3Dto1D(x, y, 0, zse_mapx(map), zse_mapy(map))])
				{
					map->chunk[zse_xyz3Dto1D(x, y+1, 0, zse_mapx(map), zse_mapy(map))] = map->chunk[zse_xyz3Dto1D(x, y, 0, zse_mapx(map), zse_mapy(map))] + map->chunk[zse_xyz3Dto1D(x, y + 1, 0, zse_mapx(map), zse_mapy(map))];
					map->chunk[zse_xyz3Dto1D(x, y, 0, zse_mapx(map), zse_mapy(map))] = 0;
				}
				else if (map->chunk[zse_xyz3Dto1D(x, y+1, 0, zse_mapx(map), zse_mapy(map))] == 0)
				{
					map->chunk[zse_xyz3Dto1D(x, y+1, 0, zse_mapx(map), zse_mapy(map))] = map->chunk[zse_xyz3Dto1D(x, y, 0, zse_mapx(map), zse_mapy(map))];
					map->chunk[zse_xyz3Dto1D(x, y, 0, zse_mapx(map), zse_mapy(map))] = 0;
				}
			}
		}
	}
	return 0;

}

int demo_2048 ()
{
	noecho();

	ST_WORLD_t *map = zse_map_init_empty_st(4, 4, 1);

	char key = ' ', fail;

	while(TRUE)
	{

		_d_2048_logic_add(map, key);

		if( (fail = _d_2048_getrandom(map, 2)) )
			return 0;

		_d_2048_draw(stdscr, 0, 0, map);
		refresh();

		key = getch();

	}

	return 0;
}