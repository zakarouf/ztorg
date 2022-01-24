#ifndef ZAKAROUF_ZSE__MAP_GENERATE_H
#define ZAKAROUF_ZSE__MAP_GENERATE_H

#include "../common.h"

double zse_map__genP2d_getSolo(double x, double y, double freq, int depth);
int zse_map__genP2d_GetNoiseSeed(void);
void zse_map__genP2d_SetNoiseSeed(int seed);

#endif

