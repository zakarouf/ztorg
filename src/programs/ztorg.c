#include "../zse/zse_all/zse_all.h"
#include <stdlib.h>

#ifdef Z_FREE_ROTATION
#define TURN_SPEED Z_TURN_FREELOOK
#define playermoveX(angle, spd) sinf(angle) * spd
#define playermoveY(angle, spd) cosf(angle) * spd


#else
#define TURN_SPEED Z_TURN_NORMAL
#define playermoveX(angle, spd) (int)sinf(angle) * spd
#define playermoveY(angle, spd) (int)cosf(angle) * spd

#endif 

enum STAT_SHOW
{
	ST_SHOW_MINI_MAP,
	ST_SHOW_HEALTH,
	ST_SHOW_MAGE,
};

/* Data */

static void ztorg_main_loop (ENTT_t *p1, ST_WORLD_t *map, TILESET_t *tileset)
{
	char quit = 0;

	float px, py;
	float mvmt_spd = 1.0f, turn_angle = TURN_SPEED;
	p1->A = 0.0f;
	p1->X = zse_rtC_getint("X ");refresh();
	p1->Y = zse_rtC_getint("Y ");refresh();
	p1->Z = zse_rtC_getint("Z ");refresh();

	uint8_t key = ' ';
	char dire[5][7]={
		{"North"},
		{"West"},
		{"South"},
		{"East"}
	};

	int8_t lkdst = 2;
		
	/*const int lookdir[4][2] = {
		LOOK_DIRECTION_N,
		LOOK_DIRECTION_W,
		LOOK_DIRECTION_S,
		LOOK_DIRECTION_E,
	};*/


	WINDOW *hud[3];
	hud[ST_SHOW_MINI_MAP] = newwin(10, 15, 2, 0);

	while (!quit)
	{
		px = p1->X;
		py = p1->Y;

		switch(key)
		{

			// Movement
			// FORWARD / BACKWARD
			case 'w':
				p1->X += playermoveX(p1->A, mvmt_spd);
				p1->Y += playermoveY(p1->A, mvmt_spd);
				break;
			case 's':
				p1->X -= playermoveX(p1->A, mvmt_spd);
				p1->Y -= playermoveY(p1->A, mvmt_spd);
				break;
			// STRAFE LEFT / RIGHT
			case 'e':
				p1->X += (int)cosf(p1->A) * mvmt_spd;
				p1->Y += (int)sinf(p1->A) * mvmt_spd;				
				break;
			case 'q':
				p1->X -= (int)cosf(p1->A) * mvmt_spd;
				p1->Y -= (int)sinf(p1->A) * mvmt_spd;
				break;
			// TURN LEFT / RIGHT
			case 'a':
				p1->A -= turn_angle;
				lkdst--;
				if(lkdst < 0)
				{
					lkdst = 3;
				}
				//direction_int -= 1;
				//if(A <= 0.0f ){A = PI_VAL*2; direction_int = 5;}
				break;
			case 'd':
				p1->A += turn_angle;
				lkdst++;
				if(lkdst > 3)
				{
					lkdst = 0;
				}
				//direction_int += 1;
				//if(A >= PI_VAL*2-1 ){A = 0; direction_int = 1;}
				break;
			// Movement END
			case 'x':
				//Shoot Wpn
				break;
			case '`':
				return;
				break;
			default:
				break;
		}

		if((p1->X < 0 || p1->Y < 0 || p1->X >= map->Xsize || p1->Y >= map->Ysize))
		{	
			p1->X = px;
			p1->Y = py;
		}


		if(!(tileset->tile[map->chunk[zse_xyz3Dto1D((int)p1->X, (int)p1->Y, (int)p1->Z, map->Xsize, map->Ysize)]].attr &TILE_ISPASS))
		{
			p1->X = px; 
			p1->Y = py;
		}

		px = p1->X;
		py = p1->Y;


		zse_r_render_world_raycast(stdscr ,p1, map, tileset->tile);
		//r_map_2D_win(hud[ST_SHOW_MINI_MAP], p1, map, tile, lookdir[lkdst][0], lookdir[lkdst][1]);
		mvaddstr(1, 1, dire[lkdst]);
		//printw(" %d %d", lookdir[lkdst][0], lookdir[lkdst][1]);
		key = getch();
	}

}


int ztorg (char name[])
{
	char *returntilesetname = malloc(ZSE_MAX_FILENAME_SIZE);

	ST_WORLD_t *map = zse_map_load_st(name , returntilesetname);
	TILESET_t tileset = zse_tileset_get(returntilesetname);

	ENTT_t *p = zse_entt_init_ENTT_t(JACK);
	p->X = 10;
	p->Y = 10;

	ztorg_main_loop (p, map, &tileset);

	zse_map_delete_st(map);
	zse_entt_delete(p);

	return 0;
}


