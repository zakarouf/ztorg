#include "entity.h"
#include <stdlib.h>

static ENTT_t *get_ho(int size)
{
	ENTT_t *e = malloc(sizeof(ENTT_t) * size);


	for (int i = 0; i < size; ++i)
	{
		e[i].status.HP = 10;
		e[i].status.XP = 0;
		e[i].status.MP = 2;
		e[i].status.SPD = 1.0f;
		e[i].sign = 2;
	}

	return e;
}

ENTTP_t zse_entt_gethostile(int size)
{
	ENTTP_t ep;
	ep.esize = size;
	ep.ent = get_ho(ep.esize);

	return ep;
}

void zse_entt_delete (ENTT_t *ent)
{
	free(ent);
}