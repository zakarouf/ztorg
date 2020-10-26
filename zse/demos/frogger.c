#include "../zse.h"

typedef struct entttt_
{
	float x;
	float y;
	float velo;

}ENTT_T;

#define ZSE_FROGGER_BASE_VELO 1.0f
#define ZSE_FROGGER_BASE_NUMB 8

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

static float getlane(float velo)
{
	int r = random() & 1;
	if(r)
	{
		return -(velo);
	}
	else
	{
		return velo;
	}
}

static ENTT_T* levelup(ST_WORLD_t * map, float *lane , int *enttsize, int level, ENTT_T *entt)
{

    free(entt);

    *enttsize = enttsize[0] + (int)(sqrt(ZSE_FROGGER_BASE_NUMB * level));

    for (int i = 0; i < map->Ysize; ++i)
    {
        lane[i] = getlane(lane[i]+0.5f);
    }


    ENTT_T *enttnew = malloc(sizeof(ENTT_T) * enttsize[0]);

    return enttnew;
}

int demo_frogger()
{
	ST_WORLD_t *map = zse_map_init_empty_st(20, 10, 2);
	float lane[map->Ysize];
    for (int i = 0; i < map->Ysize; ++i)
    {
        lane[i] = getlane(ZSE_FROGGER_BASE_VELO);
    }

    int enttsize = 8;
    int level = 0;
    int score = 0;
    int up = map->Ysize;
    ENTT_T *entt;
    entt = levelup(map, lane, &enttsize, level, NULL);
    initialize_entt(lane ,entt, enttsize, map->Xsize, map->Ysize, TRUE);


    SPRITES_t *spr = malloc(sizeof(SPRITES_t) * 2);
    spr[0] = zse_sprites_sin_load("frog");
    spr[1] = zse_sprites_sin_load("car");

	
	

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
                    if(y < up)
                    {
                        up--;
                        score += 10 + (10 * level);
                    }
				}
                else{
                    clear();
                    mvprintw(getmaxy(stdscr)/2, getmaxx(stdscr)/2, "Level %d", level+1);
                    refresh();
                    nodelay(stdscr, FALSE);
                    getch();

                    level++;
                    entt = levelup(map, lane, &enttsize, level, entt);
                    initialize_entt(lane ,entt, enttsize, map->Xsize, map->Ysize, TRUE);
                    y = map->Ysize-1;
                    nodelay(stdscr, TRUE);
                    zse_map_delete_st(map);
                    map = zse_map_init_empty_st(20, 10, 2);
                    score += 100 * level;
                    up = map->Ysize;
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

		if(map->chunk[zse_xyz3Dto1D(x, y, 1, map->Xsize, map->Ysize)] == '*')
		{
			clear();
			mvprintw(getmaxy(stdscr)/2, getmaxx(stdscr)/2 -4, "GAME OVER");
            mvprintw(getmaxy(stdscr)/2 + 1, getmaxx(stdscr)/2 -10, "SCORE: %d  LEVEL: %d", score, level);
			refresh();
			nodelay(stdscr, FALSE);
			getch();

            zse_map_delete_st(map);
            zse_delete_sprites_ptr(spr, 2);

            return 0;
		}
        
        wclear(stdscr);

		for (int i = 0; i < enttsize; ++i)
		{
			map->chunk[zse_xyz3Dto1D((int)entt[i].x ,(int)entt[i].y, 1, map->Xsize, map->Ysize)] = ' ';
			entt[i].x += entt[i].velo*time_taken;
			if(entt[i].x < 0.0f || entt[i].x > map->Xsize)
			{
				initialize_entt(lane ,&entt[i], 1, map->Xsize, map->Ysize, FALSE);
			}
			map->chunk[zse_xyz3Dto1D((int)entt[i].x ,(int)entt[i].y, 1, map->Xsize, map->Ysize)] = '*';

            zse_r_sprite(stdscr, zse_r_ssmooth(entt[i].x, spr[1].Y), (int)entt[i].y*spr[1].Y, &spr[1], 0); // Show Cars

		}
        zse_r_sprite(stdscr, x*spr[0].X, y*spr[0].Y, &spr[0], 0); // Show Player(Frog)
        mvprintw(0, 0, "Score : %d    Level : %d", score, level);

		wrefresh(stdscr);
		end_time = clock();
		time_taken = (double)(end_time - start_time) / CLOCKS_PER_SEC;
	}


	return 0;
}