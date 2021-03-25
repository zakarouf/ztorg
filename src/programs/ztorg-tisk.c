#include <stdio.h>
#include <string.h>
#include <math.h>

#include "../zse/zse.h"
#include "../zse/io/tisk/tisk.h"


#ifdef Z_FREE_ROTATION
	#define TURN_SPEED Z_TURN_FREELOOK
	#define playermoveX(angle, spd) sinf(angle) * spd
	#define playermoveY(angle, spd) cosf(angle) * spd

#else
	#define TURN_SPEED Z_TURN_NORMAL
	#define playermoveX(angle, spd) (int)sinf(angle) * spd
	#define playermoveY(angle, spd) (int)cosf(angle) * spd

#endif

#define ZSE_rtT_COLORSTR_TMPL_SIZE sizeof("\x1b[38;5;000m|")

static char screen[(zse_rtT_getmaxy() * zse_rtT_getmaxx()) + 1];
static char colorPool[256][ZSE_rtT_COLORSTR_TMPL_SIZE];
static char colormap[zse_rtT_getmaxx()];


void zse_rtT_initscr()
{

	for (int i = 0; i < 256; ++i)
	{
		snprintf(colorPool[i], ZSE_rtT_COLORSTR_TMPL_SIZE, "\x1b[38;5;%dm", i);
	}

	memset(colormap, 0, zse_rtT_getmaxx());
}

void zse_rtT_endscr()
{

}

static void showminmap_render_tisk (ENTT_t *player, ST_WORLD_t *map, TILE_t *tile)
{
	printf("\n%.1f, %.1f, z->%.0f, A->%.3f\n", player->X, player->Y, player->Z,player->A);

	for (int i = 0; i < map->Ysize; ++i)
	{
		for (int j = 0; j < map->Xsize; ++j)
		{
			if (player->X == j && player->Y == i)
			{
				putc('@', stdout);
			} else {
				putc( tile[map->chunk[zse_xyz3Dto1D(j, i, (int)player->Z, map->Xsize, map->Ysize)]].symb, stdout);	
			}
			
		}
		putchar('\n');
	}
	putc('\n', stdout);
}

static void raycast_render_tisk (ENTT_t *player, ST_WORLD_t *map, TILE_t *tile)
{
	#define SHADEMAX 11
	char shades[SHADEMAX] = {
		//' ', '.', ',', '"', ':', '+', '=', '#', '$', '$', '$', '$'
		  '@', 'M', 'h', 'h', ':', ':', '.', '.', '.', ' ', ' '
		// 1.   2.   3.   4.   5.   6.   7.   8.   9.   10.  11.  12
	};
	int shade = 0;
	char * scrptr;
	
	memset(screen, ' ', sizeof(char) * zse_rtT_getmaxx()*zse_rtT_getmaxy() +1);

	for (int x = 0; x < zse_rtT_getmaxx(); x++) 
	{
		scrptr = &screen[x];
		float ray_angle = (player->A - FOV / 2.0f) + ((float)x / (float)zse_rtT_getmaxx() * FOV);

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

				out_of_bounds = 1;
				ray_distance = DEPTH;
			}
			else {
				if((     tile[map->chunk[zse_xyz3Dto1D(testX, testY, (int)player->Z, map->Xsize, map->Ysize)]].attr & TILE_ISBLOC) 
					&& !(tile[map->chunk[zse_xyz3Dto1D(testX, testY, (int)player->Z, map->Xsize, map->Ysize)]].attr & TILE_ISINVI)) 
				{
					chech_if_hitwall = 1;
					colormap[x] = tile[map->chunk[zse_xyz3Dto1D(testX, testY, (int)player->Z, map->Xsize, map->Ysize)]].coloc;
				}
			}	
		}

		int ceiling = (zse_rtT_getmaxy() / 2) - zse_rtT_getmaxy() / (ray_distance);
		int floor = zse_rtT_getmaxy() - ceiling;


		shade = (int)((ray_distance/DEPTH) * SHADEMAX + 0.5);

		
		for (int y = 0; y < zse_rtT_getmaxy(); y++)
		{
			if(y > ceiling && y <= floor){
				*scrptr = shades[shade];
			}
			scrptr += zse_rtT_getmaxx();
		}

	}


	for (int i = 0; i < zse_rtT_getmaxy(); ++i)
	{
		screen[i*zse_rtT_getmaxx()] = '\n';		
	}


	// Draw Screen
	zse_rtT__set00();
	fwrite(screen, sizeof(char) * zse_rtT_getmaxx()*zse_rtT_getmaxy() +1, 1, stdout);

	fflush(stdout);

}




static void zt_tisk_main(ENTT_t *p1, ST_WORLD_t *map, TILESET_t *tileset)
{
	char quit = 0;

	float px, py, pz;
	float mvmt_spd = 1.0f, turn_angle = TURN_SPEED;
	p1->A = 0.0f;
	p1->X = 2.0f;
	p1->Y = 2.0f;
	p1->Z = 0.0f;

	uint8_t key = ' ';

	int8_t lkdst = 2;
		
	/*const int lookdir[4][2] = {
		LOOK_DIRECTION_N,
		LOOK_DIRECTION_W,
		LOOK_DIRECTION_S,
		LOOK_DIRECTION_E,
	};*/



	while (!quit)
	{

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
			case '`':
				return;
				break;
			case 'z':
				p1->Z += 1;
				break;
			case 'x':
				p1->Z -= 1;
				break;
			default:
				break;
		}

		if((p1->X < 0 || p1->Y < 0 || p1->X >= map->Xsize || p1->Y >= map->Ysize))
		{	
			p1->X = px;
			p1->Y = py;
		}
		if (p1->Z < 0 || p1->Z >= map->Zsize)
		{
			p1->Z = pz;
		}


		if(!(tileset->tile[map->chunk[zse_xyz3Dto1D((int)p1->X, (int)p1->Y, (int)p1->Z, map->Xsize, map->Ysize)]].attr &TILE_ISPASS))
		{
			p1->X = px; 
			p1->Y = py;
		}

		px = p1->X;
		py = p1->Y;
		pz = p1->Z;


		
		raycast_render_tisk(p1, map, tileset->tile);
		showminmap_render_tisk(p1, map, tileset->tile);
		
		key = zse_rtT_getkey();
	}
	
}

int ztorg_tisk()
{
	zse_rtT_initscr();

	char name[] = "zak";
	z__String returntilesetname = z__String_create(ZSE_MAX_FILENAME_SIZE);

	ST_WORLD_t *map = zse_map_load_st(name , returntilesetname.data);
	TILESET_t tileset = zse_tileset_get(returntilesetname.data);

	ENTT_t *p = zse_entt_init_ENTT_t(JACK);
	p->X = 10;
	p->Y = 10;


	zse_rtT_init();
	zse_rtT_hideCursor();
	zse_rtT__set00();
	zse_rtT_showCursor();


	zt_tisk_main (p, map, &tileset);

	zse_rtT_exit();

	zse_map_delete_st(map);
	zse_entt_delete(p);

	return 0;	
}
