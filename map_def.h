#ifndef MAP_DEF_H
#define MAP_DEF_H

#include <stdint.h>
#include "t_def.h"


#define MAX_MAP_WIDTH 512
#define MAX_MAP_HEIGHT 512

#define DIRECTION_NORTH	0
#define DIRECTION_SOUTH	1
#define DIRECTION_EAST	2
#define DIRECTION_WEST	3

typedef char* mdata_t;
typedef unsigned short cordinate_t;

#define index(x, y, z, X, Y) x + (y*X) + (z*X*Y)

struct Link {
	uint16_t **gx;
	uint16_t **gy;
	uint16_t **px;
	uint16_t **py;
	char *linkname;
};

struct Entity {
	struct Link link;
	char *neighbour[4];
};



typedef struct{
	uint16_t X;
	uint16_t Y;
	//struct Entity ent;
	char name[32];
	uint8_t **world;
} MAP;


/*
---------------------------------------------------------------------
MAP CONFIG FORMAT
---------------------------------------------------------------------*/
#define LINK_FILE "link"
#define WORLD_FILE "world"
#define NEIGHBOUR "[NEIGHBOUR]"
#define VACANT_MAP "VACANT_MAP_1"
/*---------------------------------------------------------------------*/


#endif