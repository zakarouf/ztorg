#ifndef TERRAIN_DEFINE_H
#define TERRAIN_DEFINE_H

#include <stdbool.h>
#include <stdint.h>

#include "z_config.h"

#define TILE_ISINVI 0x1
#define TILE_ISWALL 0x2
#define TILE_ISMOVE 0x4
#define TILE_ISDEST 0x8
#define TILE_ISFLUD 0x10
#define TILE_ISTOXI 0x20
#define TILE_ISWALK 0x40
#define TILE_ISFUNC 0x80


//----Future---Proofing----//

//#define TILE_IS 0x100
//#define TILE_IS 0x200
//#define TILE_IS 0x400
//#define TILE_IS 0x800
//#define TILE_IS 0x1000
//#define TILE_IS 0x2000
//#define TILE_IS 0x4000
//#define TILE_IS 0x8000
//#define TILE_IS 0x10000
//#define TILE_IS 0x20000
//#define TILE_IS 0x40000
//#define TILE_IS 0x80000
//#define TILE_IS 0x100000
//#define TILE_IS 0x200000
//#define TILE_IS 0x400000
//#define TILE_IS 0x800000
//#define TILE_IS 0x1000000
//#define TILE_IS 0x2000000
//#define TILE_IS 0x4000000
//#define TILE_IS 0x8000000
//#define TILE_IS 0x10000000
//#define TILE_IS 0x20000000
//#define TILE_IS 0x40000000
//#define TILE_IS 0x80000000
//#define TILE_IS 0x100000000
//#define TILE_IS 0x200000000
//#define TILE_IS 0x400000000
//#define TILE_IS 0x800000000
//#define TILE_IS 0x1000000000
//#define TILE_IS 0x2000000000
//#define TILE_IS 0x4000000000
//#define TILE_IS 0x8000000000
//#define TILE_IS 0x10000000000
//#define TILE_IS 0x20000000000
//#define TILE_IS 0x40000000000
//#define TILE_IS 0x80000000000
//#define TILE_IS 0x100000000000
//#define TILE_IS 0x200000000000
//#define TILE_IS 0x400000000000
//#define TILE_IS 0x800000000000
//#define TILE_IS 0x1000000000000
//#define TILE_IS 0x2000000000000
//#define TILE_IS 0x4000000000000
//#define TILE_IS 0x8000000000000
//#define TILE_IS 0x10000000000000
//#define TILE_IS 0x20000000000000
//#define TILE_IS 0x40000000000000
//#define TILE_IS 0x80000000000000
//#define TILE_IS 0x100000000000000
//#define TILE_IS 0x200000000000000
//#define TILE_IS 0x400000000000000
//#define TILE_IS 0x800000000000000
//#define TILE_IS 0x1000000000000000
//#define TILE_IS 0x2000000000000000
//#define TILE_IS 0x4000000000000000
//#define TILE_IS 0x8000000000000000

//----TILE--PROPS---END---//

#define TILE_ISINVI_SHIFT 1
#define TILE_ISWALL_SHIFT 2
#define TILE_ISMOVE_SHIFT 3
#define TILE_ISDEST_SHIFT 4
#define TILE_ISFLUD_SHIFT 5
#define TILE_ISTOXI_SHIFT 6
#define TILE_ISWALK_SHIFT 7
#define TILE_ISFUNC_SHIFT 8



typedef uint16_t attribute_bit_t;
#define MAX_ATTRIBUTE 16

typedef struct Tileset
{
	char name_id[32];
	uint8_t symb;
	uint8_t coloc;
	attribute_bit_t attr;

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


// DEF
#define TILESET_DEFAULT "DEFAULT"

#endif