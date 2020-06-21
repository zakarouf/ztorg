/*
-----------------------------------------------------


-----------------------------------------------------*/
#include <math.h>
#include <stdint.h>

#include "it_common.h"
#include "map.h"

uint16_t w_damage[TOTAL_WEAPONS] = 
{
	5, 2, 4, 1, 4, 2, 4, 1, 0
};

uint16_t w_range[TOTAL_WEAPONS] =
{
	1, 6, 4, 6, 5, 3, 3, 6, 1
};

/*void set_up_weaponstats () {

}

int w_hit_wrapup (int w_id) {

}
*/

int w_hitdamage_check (int x,int y, float angle, int w_id)
{
	int check_distance = 0;

	float p_eyeX = sinf(angle);
	float p_eyeY = cosf(angle);

	while (check_distance <= w_range[w_id]) {

		check_distance ++;

		int testX = (int)(x + p_eyeX * check_distance);
		int testY = (int)(y + p_eyeY * check_distance);

		if (map1.world[testY][testX] != ' ') {
			return w_damage[w_id];
		}
	}
	return 0;
}