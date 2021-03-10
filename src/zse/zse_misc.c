#include "zse.h"

int	zse_delete_all(TILESET_t *t, ST_WORLD_t *map, ENTT_t *ent)
{
	if (map != NULL)
	{
		zse_map_delete_st(map);	
	}
	
	if (t != NULL)
	{
		zse_tileset_delete(t);
	}
	
	if (ent != NULL)
	{
		zse_entt_delete (ent);	
	}
	

	return 0;
}
