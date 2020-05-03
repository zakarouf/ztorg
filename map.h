#ifndef MAP_H
#define MAP_H

typedef struct{
	int X;
	int Y;
	int crnt;
	int link[32][4];
	char name[54];
	char neighbour[4][54];
	char linkname[32][54];
	char world[256][256];

} MAP;

#define MAX_MAP_WIDTH 256

MAP mapED;
MAP map1;
#endif