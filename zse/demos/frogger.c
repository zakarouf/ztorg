#include "../zse.h"

typedef struct entttt_
{
	float x;
	float y;
	float velo;

}ENTT_T;

const char frogger_car[4][4]={
    {' ',' ','_','\\'},
    {'-','/',' ','|'},
    {'-','-','-','='},
    {'*',' ',' ','*'}
};

const char frogger_frog[4][4]={
    {' ','0','0',' '},
    {'(','-','-',')'},
    {' ','(',')',' '},
    {' ','H','H',' '}
};

static void initialize_entt(float lane[] ,ENTT_T * entt, int population, int mapx, int mapy, char f)
{
	for (int i = 0; i < population; ++i)
	{
		entt[i].y = (float)(random() % mapy-1);
		if(lane[(int)entt[i].y] > 0.0f)
		{
			entt[i].x = 0.0f;
		}
		else
		{	
			entt[i].x = mapx-1.0f;
		}
		entt[i].velo = lane[(int)entt[i].y];
		if (f)
		{
			entt[i].x = (float)(random() % mapx);
		}
		
	}
}

static void draw(ST_WORLD_t *map, ENTT_T *entt, int enttsize, const int tilesize)
{
	for (int s = 0; s < enttsize; ++s)
	{
		for (int i = 0; i < tilesize; ++i)
		{
			for (int j = 0; j < tilesize; ++j)
			{
				mvwaddch(stdscr, (int)entt[s].y*tilesize +i , (int)entt[s].x*tilesize +j , frogger_car[i][j]);
			}
		}
	}
		
	

}

static float getlane()
{
	int r = random() & 2;
	if(r)
	{
		return -1.9f;
	}
	else
	{
		return 1.9f;
	}
}

int frogger()
{
	ST_WORLD_t *map = zse_map_init_empty_st(20, 10, 2);
	float lane[map->Ysize];
	int tilesize = 4;

	for (int i = 0; i < map->Ysize; ++i)
	{
		lane[i] = getlane();
	}

	int enttsize = 60;
	ENTT_T *entt = malloc(sizeof(ENTT_T) * enttsize);
	initialize_entt(lane ,entt, enttsize, map->Xsize, map->Ysize, TRUE);

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
                else{
                    clear();
                    mvprintw(getmaxy(stdscr)/2, getmaxx(stdscr)/2, "YOU WON");
                    refresh();
                    nodelay(stdscr, FALSE);
                    getch();

                    return 0;
                }
				break;
			case 's':
				if(y <= map->Ysize)
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
				if(x <= map->Xsize)
				{
					x++;
				}
				break;

			default:break;
		}

		if(map->chunk[getindex3d(x, y, 1, map->Xsize, map->Ysize)] == '*')
		{
			clear();
			mvprintw(getmaxy(stdscr)/2, getmaxx(stdscr)/2, "GAME OVER");
			refresh();
			nodelay(stdscr, FALSE);
			getch();
			return 0;
		}

		for (int i = 0; i < enttsize; ++i)
		{
			map->chunk[getindex3d((int)entt[i].x ,(int)entt[i].y, 1, map->Xsize, map->Ysize)] = ' ';
			entt[i].x += entt[i].velo*time_taken;
			if(entt[i].x < 0.0f || entt[i].x > map->Xsize)
			{
				initialize_entt(lane ,&entt[i], 1, map->Xsize, map->Ysize, FALSE);
			}
			map->chunk[getindex3d((int)entt[i].x ,(int)entt[i].y, 1, map->Xsize, map->Ysize)] = '*';

		}
		clear();
		draw(map, entt, enttsize, tilesize);

		for (int i = 0; i < tilesize; ++i)
		{
			for (int j = 0; j < tilesize; ++j)
			{
				mvwaddch(stdscr, y*tilesize +i, x*tilesize +j, frogger_frog[i][j]);
			}
		}
		


		refresh();
		end_time = clock();
		time_taken = (double)(end_time - start_time) / CLOCKS_PER_SEC;
	}


	return 0;
}