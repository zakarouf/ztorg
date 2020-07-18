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


// Perlind stuff
double c_perlin2d_get_solo(double x, double y, double freq, int depth);
void c_set_perlin_seed(int seed);

#endif