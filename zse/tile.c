#include "tile_lib.h"
#include <string.h>
#include <sys/stat.h>


static TILE_t* _tile_getdefault()
{
	TILE_t *tileset = malloc(sizeof(TILE_t) * 8);

	char tile_desc[8][16] = {
			{"Floor/Space"},
			{"WALL"},
			{"WALL_MOVEABLE"},
			{"WALL_BREAKABLE"},
			{"WALL_INVISIBLE"},
			{"FLOOR_TOXIC"},
			{"FLOOR_WATER"},
			{"FLOOR_NULL"},
		};

	attribute_bit_t attr[8] = {

		TILE_ISPASS,				// 000 AIR
		TILE_ISBLOC,				// 001 WALL 
		TILE_ISBLOC | TILE_ISMOVE,	// 002 WALL_MOVEABLE
		TILE_ISBLOC | TILE_ISDEST,	// 003 WALL_BREAKABLE
		TILE_ISBLOC | TILE_ISINVI,	// 004 WALL_INVISIBLE
		TILE_ISPASS | TILE_ISTOXI,	// 005 FLOOR_TOXIC
		TILE_ISPASS | TILE_ISFLUD,	// 006 FLOOL_WATER
		TILE_ISPASS,				// 007 FLOOR_NULL
	};

	uint8_t 
		symb[8] = 
		{'.', '#', '#', '#', '#', '%', '~', ' '},
		colo[8] = 
		{1, 1, 2, 1, 1, 1, 1, 1};

	for(int i = 0; i < 8; i++)
		{
			sprintf(tileset[i].name_id,"%s", tile_desc[i]);
			tileset[i].coloc = colo[i];
			tileset[i].symb = symb[i];
			tileset[i].attr = attr[i];
			//tileset[i].tex_id = 0;
		}

	return tileset;
}

static TILE_t* _tile_load_maindata(char dirpos[])
{
	FILE *fp = fopen(dirpos, "r");
	char ver[8];
    fread(ver, sizeof(ver), 1, fp);
    int tilenum;
    fread(&tilenum, sizeof(int), 1, fp);

    TILE_t *tile = malloc(sizeof(TILE_t) * tilenum);

    fread(tile, sizeof(TILE_t), tilenum, fp);

    fclose(fp);

    return tile;

}

TILE_t* zse_tile_realloc (int *old_size, int new_size, TILE_t *tile)
{
	TILE_t *tmp = tile;
	tmp = realloc (tile, sizeof(TILE_t) * new_size);

	if(tmp == NULL)
	{
		// Reallocation Fails Do Nothing. Return As Is
		return tile;
	}

	else {

		// Realloction Success. Initilize new formed tiles.
		for (int i = *old_size; i < new_size ; i++)
		{
			sprintf(tmp[i].name_id, "NULL");
			//tile[i].tex_id = 0;
			tmp[i].symb = 32;
			tmp[i].coloc = 0;
			tmp[i].attr = 0;
		}
		
		*old_size = new_size;
		return tmp;
	}
}


TILE_t* zse_tile_intiempty (int t_size)
{
	TILE_t *tile = malloc(sizeof(TILE_t) * t_size);

	for (int i = 0; i < t_size ; i++)
	{
		sprintf(tile[i].name_id, "NULL");
		//tile[i].tex_id = 0;
		tile[i].symb = 32;
		tile[i].coloc = 0;
		tile[i].attr = 0;
	}
	
	return tile;
}

TILE_t *zse_tile_load(char name[], int *size)
{
	if(strcmp(name, TILE_DEFAULTTILESET) == 0)
	{
		return _tile_getdefault();
	}

	char tile_dir[64] = TILE_PARENTDIR;
	char dirpos[72];

	strncat(tile_dir, name, 64);
	sprintf(dirpos, "%s/%s", tile_dir, TILE_TILEDATA_FILE);
	TILE_t *tile = _tile_load_maindata(dirpos);



	return tile;
}

int zse_tile_export(TILE_t *tile, int size ,char name[], bool newtile)
{
	char tile_dir[64] = TILE_PARENTDIR;
	char dirpos[72];

	strncat(tile_dir, name, 64);
	sprintf(dirpos, "%s/%s", tile_dir, TILE_TILEDATA_FILE);

	if(newtile)
	{
		mkdir(tile_dir, 0777);
	}

	FILE *fp;
	if((fp = fopen(dirpos, "w")) == NULL)
	{
		printw("%s",dirpos);
		printw("UNABLE To Creat Tile File\n");
		getch();
		return -1;
	}

	fwrite(ZSE_ENGINE_VERSION, sizeof(char), 8, fp);
	fwrite(&size, sizeof(int), 1, fp);
	fwrite(tile, sizeof(TILE_t), size, fp);

	fclose(fp);
	return 0;
}
