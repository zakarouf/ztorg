/*
-----------------------------------------------------
This is Map Loading & Exporting Segment
----------------------------------------------------*/

#include "map_lib.h"

#include <sys/stat.h>
#include <string.h>

/*-----IN_WORLD-----*/
//---------------------------











/*-----ST_WORLD-----*/
//---------------------------

//----------------------------------------------//
//Write
//----------------------------------------------//

static int _map_export_plotdatadata_st(plotdata_t *chunk, int X, int Y, int Z, char dirpos[])
{
    FILE *fp = fopen(dirpos, "w");

    fwrite(chunk, sizeof(plotdata_t)* (X * Y* Z), 1, fp);

    fclose(fp);

    return 0;
}

static int _map_export_commondata_st(ST_WORLD_t *map, char tilesetname[],char dirpos[])
{

	FILE *fp = fopen(dirpos, "w");

    fwrite(ZSE_ENGINE_VERSION, sizeof(char), 8, fp);
    fwrite(map, sizeof(ST_WORLD_t) - sizeof(plotdata_t*), 1, fp);
    fwrite(tilesetname, 32, 1, fp);

    fclose(fp);

    return 0;
}



//----------------------------------------------//
//Read
//----------------------------------------------//

static int _map_load_plotdata_st (ST_WORLD_t* m, char dirpos[])
{
    FILE *fp = fopen(dirpos, "r");
    m->chunk = (plotdata_t*) malloc(sizeof(plotdata_t)*m->Xsize*m->Ysize*m->Zsize);

    fread(m->chunk, sizeof(plotdata_t)* m->Zsize * m->Ysize* m->Xsize, 1, fp);

    fclose(fp);

    return 0;
}

static int _map_load_commondata_st (ST_WORLD_t *map, char *returntilesetname, char dirpos[])
{
	FILE *fp = fopen(dirpos, "r");
    

    char ver[8];
    fread(ver, sizeof(ver), 1, fp);
    printf("version : %s\n", ver);
    fread(map, sizeof(ST_WORLD_t) - sizeof(plotdata_t*), 1, fp);
    fread(returntilesetname, sizeof(char), ZSE_MAX_FILENAME_SIZE, fp);

    fclose(fp);

    return 0;
}

//------------------Map_load_ex-------------------//

int zse_map_export_st(ST_WORLD_t *map, char name[], char tilesetname[], bool newmap)
{
	char mapdir[48] = MAP_DIR_NAME;
	char dirpos[74] = "";
	strcat(mapdir, name);

	if (newmap)
	{
		mkdir(mapdir, 0777);
	}

	sprintf(dirpos, "%s/%s", mapdir, MAP_DATAFILE_COMMON);
	_map_export_commondata_st(map, tilesetname, dirpos);


	sprintf(dirpos, "%s/%s", mapdir, MAP_DATAFILE_WORLD);
	_map_export_plotdatadata_st(map->chunk, map->Xsize, map->Ysize, map->Zsize, dirpos);

	
	return 0;

}


ST_WORLD_t* zse_map_load_st (char name[], char *returntilesetname)
{
	ST_WORLD_t *map = malloc(sizeof(ST_WORLD_t));

	char mapdir[48] = MAP_DIR_NAME;
	char dirpos[74] = "";
	strcat(mapdir, name);

	sprintf(dirpos, "%s/%s", mapdir, MAP_DATAFILE_COMMON);
	_map_load_commondata_st(map, returntilesetname, dirpos);

	sprintf(dirpos, "%s/%s", mapdir, MAP_DATAFILE_WORLD);
	_map_load_plotdata_st(map, dirpos);



	return map;
}