#ifndef TERRAIN_DEFINE_H
#define TERRAIN_DEFINE_H

#include <stdbool.h>
#include <stdint.h>

typedef struct TILEATTR
{
	bool isinvi;
	bool iswall;
	bool ismove;
	bool isbreak;
	bool isliquid;
	bool istoxic;
	bool iswalk;
}TILEATTR;


typedef struct
{
	char name_id[16];
	uint8_t tex_id;
	uint8_t symb;
	uint8_t coloc;
	TILEATTR attr;

}TILE;


enum
{
	SPACE_FLOOR ,
	WALL,
	WALL_MOVEABLE,
	WALL_BREAKABLE,
	WALL_INVISIBLE,
	FLOOR_TOXIC,
	FLOOL_WATER,
	FLOOR_NULL,
};


#endif