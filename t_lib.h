#ifndef TERRAIN_LIB_H
#define TERRAIN_LIB_H

#include "t_def.h"

#define TILESET_DEFAULT "DEFAULT"

TILE* t_calloc_tile (int t_size);
int t_apply_tileattr (attribute_bit_t *tile, int attr_int);
TILE *init_TILESET (char tileset_name[]);

#endif