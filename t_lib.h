#ifndef TERRAIN_LIB_H
#define TERRAIN_LIB_H

#include "t_def.h"

#define TILESET_DEFAULT "DEFAULT"

TILE* t_malloc_initempty_tile (int t_size);
TILE* t_realloc_initempty_tile (int *old_size, int new_size, TILE *tile);

TILE *init_TILESET (char tileset_name[], int *maxtile);


int t_maker_main ();


void t_deltile (TILE *);

#endif