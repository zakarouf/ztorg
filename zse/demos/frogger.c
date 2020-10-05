#include "../zse.h"

typedef struct entttt_
{
	float x;
	float y;
	char velo;

}ENTT_T;

static void initialize_entt(ENTT_T * entt, int population, int mapx, int mapy)
{
	for (int i = 0; i < population; ++i)
	{
		entt[i].y = (float)(random() & 7);
		entt[i].x = (float)(random() % mapx);
		int r = random() &1;
		if(r)
		{
			entt[i].velo = -1;
		}
		else
		{
			entt[i].velo = 1;
		}
		
	}
}

static void draw(ST_WORLD_t *map, ENTT_T *entt, int enttsize)
{
	for (int i = 0; i < map->Ysize; ++i)
	{
		for (int j = 0; j < map->Xsize; ++j)
		{
			for (int s = 0; s < enttsize; ++s)
			{
				mvwaddch(stdscr, (int)entt[s].y, (int)entt[s].x, '*');
			}
		}
	}
	refresh();
}

int frogger()
{
	ST_WORLD_t *map = zse_map_init_empty_st(20, 10, 2);

	int enttsize = 8;
	ENTT_T *entt = malloc(sizeof(ENTT_T) * enttsize);
	initialize_entt(entt, enttsize, map->Xsize, map->Ysize);

	int x = map->Xsize/2, y = map->Ysize-1;
	char key;

	clock_t start_time = 0.0f, end_time = 0.0f;
	double time_taken;


	nodelay(stdscr, TRUE);

	while(TRUE)
	{
		start_time = clock();
		key = getch();

		switch(key){
			case 'w':
				if(y > 0)
				{
					y--;
				}
				break;
			case 's':
				if(y < map->Ysize)
				{
					y++;
				}
				break;
			case 'a':
				if(x > 0)
				{
					x--;
				}
				break;
			case 'd':
				if(x < map->Xsize)
				{
					x++;
				}
				break;

			default:break;
		}

		for (int i = 0; i < enttsize; ++i)
		{
			entt[i].x += entt[i].velo*time_taken;
			if(entt[i].x < 0.0f || entt[i].x > map->Xsize)
			{
				initialize_entt(&entt[i], 1, map->Xsize, map->Ysize);
			}
		}
		clear();
		draw(map, entt, enttsize);
		mvwaddch(stdscr, y, x, '@');
		
		end_time = clock();
		time_taken = (double)(end_time - start_time) / CLOCKS_PER_SEC;
	}


	return 0;
}