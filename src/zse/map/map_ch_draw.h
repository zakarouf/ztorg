#ifndef ZAKAROUF_ZSE__MAP_CHUNKTYPE_DRAW_n_MANIPULATE_H
#define ZAKAROUF_ZSE__MAP_CHUNKTYPE_DRAW_n_MANIPULATE_H

#include "map_ch_def.h"

void zse_map__draw_rect_raw(zset__mapChPlot *chunk, z__Vint2 bounds, z__Vint2 from, z__Vint2 to, int level, zset__mapChPlot plot);
void zse_map__draw_circle_raw(zset__mapChPlot *chunk, z__Vint3 on, z__Vint2 bounds , z__i32 r, zset__mapChPlot plot);

#define zse_map__ch_draw_rect(map, ch_num, from, to, level, plot)

#endif
