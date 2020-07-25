/*
-----------------------------------------------------
MAIN GAME SEGMENT
----------------------------------------------------*/

#include "r_lib.h"
#include "p_lib.h"
#include "g_lib.h"

#include "map_def.h"

//---------------------------------------------------//
#define TURN_SPEED DEGREE_90
//---------------------------------------------------//

enum STAT_SHOW
{
	ST_SHOW_MINI_MAP,
	ST_SHOW_HEALTH,
	ST_SHOW_MAGE,
};

#ifdef Z_FREE_ROTATION
#define shootweapon 1
#else
#define shootweapon 0
#endif 

void g_main_loop (PLAYER *p1, MAP *map, TILE *tile)
{
	bool quit = 0;

	float px, py;
	float mvmt_spd = 1.0f, turn_angle = TURN_SPEED;

	uint8_t key = ' ';
	char dire[5][7]={
		{"North"},
		{"West"},
		{"South"},
		{"East"}
	};

	int8_t lkdst = 2,
		lookdir[4][2] = {
		LOOK_DIRECTION_N,
		LOOK_DIRECTION_W,
		LOOK_DIRECTION_S,
		LOOK_DIRECTION_E,
	};


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
				p1->X += (int)sinf(p1->A) * mvmt_spd;
				p1->Y += (int)cosf(p1->A) * mvmt_spd;
				break;
			case 's':
				p1->X -= (int)sinf(p1->A) * mvmt_spd;
				p1->Y -= (int)cosf(p1->A) * mvmt_spd;
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
				quit ^= 1;
				break;
			default:
				break;
		}

		if((p1->X < 0 || p1->Y < 0 || p1->X >= map->X || p1->Y >= map->Y))
		{	
			//clear();
			//switch_neighbour(x, y);
			p1->X = px;
			p1->Y = py;
		}

		if(tile[map->world[(int)p1->Y][(int)p1->X]].attr &TILE_ISMOVE)
		{
			int tmptile = map->world[(int)p1->Y][(int)p1->X];
			if(key == 'w')
			{
				if(map->world[(int)(p1->Y+cosf(p1->A)*mvmt_spd)][(int)(p1->X+sinf(p1->A)*mvmt_spd)] == 0)
				{
					map->world[(int)p1->Y][(int)p1->X] = 0;
					map->world[(int)(p1->Y+(int)cosf(p1->A)*mvmt_spd)][(int)(p1->X+(int)sinf(p1->A)*mvmt_spd)] = tmptile;
				}
				else 
				{
					p1->X = px; 
					p1->Y = py;
				}
			}
		}


		if(tile[map->world[(int)p1->Y][(int)p1->X]].attr &TILE_ISWALL)
		{
			p1->X = px; 
			p1->Y = py;
		}

		px = p1->X;
		py = p1->Y;


		r_render_world_raycast(p1, map, tile);
		r_map_2D_win(hud[ST_SHOW_MINI_MAP], p1, map, tile, (int*)lookdir[lkdst]);
		mvaddstr(1, 1, dire[lkdst]);
		key = getch();
	}

}


