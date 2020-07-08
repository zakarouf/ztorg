#include "npc_lib.h"
#include "calc.h"

bool npc_find_player_pos (NPC *npc, int px, int py, int *dist)
{
	dist[0] = ((px - npc->X) * (px - npc->X)) + ((py - npc->Y) * (py - npc->Y));
	int seen_q = (dist[0] <= npc->sight * npc->sight) ? 1 : 0;


	return seen_q;
}

void npc_wanderoff (NPC *npc, MAP *map)
{

}

void npc_hostile_update (NPC *npc, MAP *map, PLAYER *p1, int npc_count)
{
	for (int i = 0; i < npc_count; ++i)
	{
		int dist;
		if(npc_find_player_pos(&npc[i], p1->X, p1->Y, &dist))
		{
			int ifhit = calc_hit_chance_range(npc->sight, npc->stat.IN, sqrt(dist), 5, p1->stat.IN);
			if (ifhit)
			{
				p1->stat.HP--;
			}
		}
		else
		{
			npc_wanderoff(npc, map);
		}
	}
}