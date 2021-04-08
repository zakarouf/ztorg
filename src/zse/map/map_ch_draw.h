#ifndef ZAKAROUF_ZSE__MAP_CHUNKTYPE_DRAW_n_MANIPULATE_H
#define ZAKAROUF_ZSE__MAP_CHUNKTYPE_DRAW_n_MANIPULATE_H

#include "map_ch_def.h"

void zse_map__draw_rec(zset__mapChPlot *chunk, z__Vint2 bounds, z__Vint3 from, z__Vint3 to, zset__mapChPlot plot);
void zse_map__draw_circle(zset__mapChPlot *chunk, z__Vint3 on, z__Vint2 bounds , z__i32 r, zset__mapChPlot plot);

#endif
