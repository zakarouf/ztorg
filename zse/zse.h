#ifndef ZTORG_MAIN_HEADER
#define ZTORG_MAIN_HEADER

#include "sys/sys.h"
#include "map/map_lib.h"
#include "r_curses/r_lib.h"
#include "tiles/tile_lib.h"
#include "sprites/sprites_lib.h"
#include "entity/entity.h"

int	zse_delete_all(TILESET_t *t, ST_WORLD_t *map, ENTT_t *ent);

#endif