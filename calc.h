#ifndef CALC_H
#define CALC_H

#include <math.h>
#include <stdint.h>

float calc_carmack_sqrt (float number);
uint64_t shift1_uint64 (int upto);


int calc_hit_chance_range
(	int sight,
	int intelligence,
	int distance,
	int wp_precision,
	int p_intelligence
);


#endif