#include "p_lib.h"

void p_hurt_player (int damage, PLAYER *p, int dist)
{
	
}


PLAYER *init_player (PLAYER *p)
{
	PLAYER *pp = p;

	pp->X = 3.0f;
	pp->Y = 3.0f;
	pp->A = 0.0f;

	pp->stat.HP = 10;
	pp->stat.XP = 0;
	pp->stat.MP = 2;

	return pp;
}