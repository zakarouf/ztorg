#include "entity.h"

ENTT_t *init_ENTT_t (ENTCLASS class)
{
	ENTT_t *pp = malloc(sizeof(ENTT_t));

	if(class == JACK)
	{
		pp->X = 3.0f;
		pp->Y = 3.0f;
		pp->A = 0.0f;

		pp->status.HP = 10;
		pp->status.XP = 0;
		pp->status.MP = 2;
		pp->status.SPD = 1.0f;
	}

	return pp;
}

void p_delENTT_t (ENTT_t *ent)
{
	free(ent);
}