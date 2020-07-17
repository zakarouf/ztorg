#ifndef TILE_IO_H
#define TILE_IO_H

#include "t_def.h"

// Read
TILE *load_custom_tile (char *tile_name, int *maxtile);

// Write
int t_create_tile (TILE *tile, char tileset_name[] ,int maxtile, bool new);

#endif