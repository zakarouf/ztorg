#ifndef ZAKAROUF_ZSE__TILE_H
#define ZAKAROUF_ZSE__TILE_H

#include "tile_def.h"

void zse_tile__tileset_deleteContent(zset__Tileset *ts);
zset__Tileset zse_tile__tileset_getDefault(void);

zset__Tileset zse_tile__tileset_load(char const filename [ static 1 ]);
void zse_tile__tileset_export(zset__Tileset *ts, char filename [ static 1 ]);

#endif
