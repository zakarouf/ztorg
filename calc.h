#ifndef CALC_H
#define CALC_H

#include <math.h>

float calc_carmack_sqrt (float number);

int calc_hit_chance_range
(	int sight,
	int intelligence,
	int distance,
	int wp_precision,
	int p_intelligence
);


#endif