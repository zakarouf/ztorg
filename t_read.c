#include <stdio.h>
#include <string.h>
#include <ncurses.h>
#include <stdlib.h>

#include "t_def.h"
#include "t_io.h"

TILE *load_custom_tile (char *tile_name, int *maxtile)
{
	char tile_dir[64] = "tiles/";
	char tile_file_name_buff[72];
	char buffer[128];

	strncat(tile_dir, tile_name, 64);
	sprintf(tile_file_name_buff, "%s/%s", tile_dir, "tload");

	FILE *fp;
	fp = fopen(tile_file_name_buff, "r");

	if(fp == NULL)
	{
		printw("NO SUCH TILESET EXIST");
		refresh();
		getch();
		return NULL;
	}

	TILE *r_tile;

	fgets(buffer, 128, fp); // get version
    fgets(buffer, 128, fp); // get XY
    sscanf(buffer, "%d", &maxtile[0]);

    if((r_tile = malloc(sizeof(TILE) * maxtile[0])) == NULL)
    {
    	printw("NO UNABLE TO ALLOCATE REQUIRED MEMORY");
    	refresh();
		getch();
    	return NULL;
    }


    for(int i = 0; i < maxtile[0]; i++)
    {
    	fscanf(fp, "%s", r_tile[i].name_id);
    }

    fgets(buffer, 128, fp);
    fgets(buffer, 128, fp);



    for(int i = 0; i < maxtile[0]; i++)
    {
    	fscanf(fp, "%hhd", &r_tile[i].symb);
    	fscanf(fp, "%hhd", &r_tile[i].coloc);
    	fscanf(fp, "%hd", &r_tile[i].attr);

    }

    fclose(fp);
    return r_tile;
}