#ifndef MAP_H
#define MAP_H

#define MAX_MAP_WIDTH 512
#define MAX_MAP_HEIGHT 512

#define DIRECTION_NORTH	0
#define DIRECTION_SOUTH	1
#define DIRECTION_EAST	2
#define DIRECTION_WEST	3


typedef struct{
	int X;
	int Y;
	int crnt;
	int link[32][4];
	char name[54];
	char neighbour[4][54];
	char linkname[32][54];
	char world[MAX_MAP_HEIGHT][MAX_MAP_WIDTH];

} MAP;

char mask[MAX_MAP_HEIGHT][MAX_MAP_WIDTH];

MAP mapED;
MAP map1;

#endif