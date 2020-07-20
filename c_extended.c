#include "c_lib.h"

int calc_calculate_damage ()
{
	int dmg = 0;

	return dmg;
}

int calc_hit_chance_range
(	int sight,
	int intelligence,
	int distance,
	int wp_precision,
	int p_intelligence
)
{

	int s_val = (100*(sight - distance))/sight;
	int r_val = s_val;

	return r_val;
}


float calc_sqrt (float number)
{
	float 
	x = number * 0.5f,
	y = number;

	int i = *(int *) &y;

	i = 0x5f3759df - (i >> 1);
	y = * (float *) &i;
	y = y * (1.5 - (x * y * y));
	y = y * (1.5 - (x * y * y));

	return number * y;
}

uint64_t shift1_uint64 (int upto)
{
	if(upto < 63)
	{
		uint64_t num = 1;
		for (int i = 0; i < upto; ++i)
		{
			num <<= 1;
		}
		return num;
	}

	else
	{
		return -1;
	}

	return 0;
}