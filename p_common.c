#include "p_lib.h"
#include <stdlib.h>

PLAYER *init_player (ENTCLASS class)
{
	PLAYER *pp = malloc(sizeof(PLAYER));

	if(class == JACK)
	{
		pp->X = 3.0f;
		pp->Y = 3.0f;
		pp->A = 0.0f;

		pp->stat.HP = 10;
		pp->stat.XP = 0;
		pp->stat.MP = 2;
	}

	return pp;
}

void p_delplayer (PLAYER *player)
{
	free(player);
}