#include "w_lib.h"
#include "map_def.h"

void w_check_if_hit_4dir(WEAPONperk_t *wpn, int dirlook_xy[2], int playerpos[2], int **map, TILE *tile)
{

	int i = 0;
	while(i < wpn->range)
	{
		int y = (dirlook_xy[0] * i) + playerpos[0];
		int x = (dirlook_xy[1] * i) + playerpos[1];
		if (!(tile[map[y][x]].attr &TILE_ISWALK))
		{
			return;
		}
		i++;
	}
	
}