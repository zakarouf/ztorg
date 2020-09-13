#ifndef ZSE_TILE_LIB_H
#define ZSE_TILE_LIB_H

#include "common.h"

#define TILE_ISINVI 0x1
#define TILE_ISBLOC 0x2
#define TILE_ISMOVE 0x4
#define TILE_ISDEST 0x8
#define TILE_ISFLUD 0x10
#define TILE_ISTOXI 0x20
#define TILE_ISPASS 0x40
#define TILE_ISFUNC 0x80


//----TILE--PROPS---END---//


typedef uint16_t attribute_bit_t;
#define MAX_ATTRIBUTE 16


typedef struct Tileset
{
	char name_id[ZSE_MAX_FILENAME_SIZE];
	uint8_t symb;
	uint8_t coloc;
	attribute_bit_t attr;

}TILE_t;


int zse_tile_export(TILE_t *tile, int size ,char name[], bool newtile);
TILE_t *zse_tile_load(char name[], int *size);

TILE_t* zse_tile_intiempty (int t_size);
TILE_t* zse_tile_realloc (int *old_size, int new_size, TILE_t *tile);


#define TILE_DEFAULTTILESET "DEFAULT"
#define TILE_PARENTDIR "tiles/"

#define TILE_TILEDATA_FILE "tile.bin"

#endif