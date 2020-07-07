#ifndef TERRAIN_LIB_H
#define TERRAIN_LIB_H

#include "t_def.h"

#define TILESET_DEFAULT "DEFAULT"

int t_apply_tileattr (TILEATTR *tile, int attr_int);
TILE *init_TILESET (char tileset_name[]);

#endif