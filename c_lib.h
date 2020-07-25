#ifndef CALC_H
#define CALC_H

#include <math.h>
#include "z_include.h"


// Quality of life stuff
#define swap2int(x, y) x ^= y; y ^= x; x ^= y
#define shift1by_u64(x) (unsigned long long)(1ULL << x)
#define shift1by_uint(x) (unsigned int)(1 << x)


// ----Mafs----
float calc_sqrt (float number);

// ----RNG_Calc--------
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