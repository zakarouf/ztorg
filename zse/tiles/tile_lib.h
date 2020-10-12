#ifndef ZSE_TILE_LIB_H
#define ZSE_TILE_LIB_H

#include "../common.h"

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
typedef uint16_t tiletexture_t;

#define MAX_ATTRIBUTE 16


typedef struct _TILE
{
	char name_id[ZSE_MAX_FILENAME_SIZE];
	uint8_t symb;
	uint8_t coloc;
	attribute_bit_t attr;

}TILE_t;

typedef struct _TILESET
{
	TILE_t *tile;
	tiletexture_t *tex;
	uint16_t tiletexsize;
	size_t tsize;

}TILESET_t;

#define zse_atttex(n, size) (n)*(size)


//int zse_tile_export(TILE_t *tile, int size ,char name[], bool newtile);
//TILE_t *zse_tile_load(char name[], int *size);

TILESET_t zse_tileset_init (void);
int zse_tileset_chsize(TILESET_t *t, size_t newsize);


TILESET_t zse_tileset_get (char name[]);
int zse_tileset_exp (char name[], TILESET_t *t, int newt);

void zse_tileset_delete(TILESET_t *t);

//TILE_t* zse_tile_intiempty (size_t t_size);
//TILE_t* zse_tile_realloc (size_t *old_size, size_t new_size, TILE_t *tile);


#define TILE_DEFAULTTILESET "DEFAULT"
#define TILE_PARENTDIR "tiles/"

#define TILE_TILEDATA_FILE "tile.bin"

#endif