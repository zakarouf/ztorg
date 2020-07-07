#include "calc.h"


int calc_calculate_damage ()
{
	int dmg = 0;

	return dmg;
}


float calc_carmack_sqrt (float number)
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