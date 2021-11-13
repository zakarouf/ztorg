#ifndef ZAKAROUF_ZSE__TILE_H
#define ZAKAROUF_ZSE__TILE_H

#include "tile_def.h"

void zse_tile__tileset_deleteContent(zse_T_Tileset *ts);
zse_T_Tileset zse_tile__tileset_getDefault(void);

zse_T_Tileset zse_tile__tileset_load(char const filename [ static 1 ]);
void zse_tile__tileset_export(zse_T_Tileset *ts, char filename [ static 1 ]);

zse_T_Tileset zse_tile__tileset_createEmpty(z__size tileCount, z__size textureCount);

#endif
