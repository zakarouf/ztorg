#include "map_update.h"
#include "map.h"
#include "map_load.h"
#include "player.h"
#include <stdint.h>


void change_map (int x, int y) {
	int i;
	for (i = 0; i < 10; ++i)
	{
		if(x == map1.link[i][0] && y == map1.link[i][1]) {
			p1.X = map1.link[i][2];
			p1.Y = map1.link[i][3];
			process_map_file(map1.linkname[i]);
		}
	}
	
}


int switch_neighbour (int x,int y) {
	uint8_t map_num;
	uint8_t check;
	if(y < 0) {
		map_num = 0;
	}
	else if(y >= map1.Y) {
		map_num = 1;
	}
	else if(x < 0) {
		map_num = 2;
	}
	else if(x >= map1.X) {
		map_num = 3;
	}
	else {
		return -1;
	}

	check = process_map_file(map1.neighbour[map_num]);

	if(check == 0) {

		if(y < 0) {
			p1.Y = map1.Y - 1;
		}
		else if(y >= map1.Y) {
			p1.Y = 0;
		}
		else if(x < 0) {
			p1.X = map1.X - 1;
		}
		else if(x >= map1.X) {
			p1.X = 0;
		}
		else {
		 return -1;
		}
	}
	return 0;

}