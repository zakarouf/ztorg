#include "t_def.h"
#include "t_io.h"

#include <stdio.h>
#include <string.h>
#include <ncurses.h>
#include <stdlib.h>
#include <sys/stat.h>

int t_create_tile (TILE *tile, char tileset_name[] ,int maxtile, bool new)
{
	char tile_dir[64] = "tiles/";
	char tile_file_name_buff[72];

	strncat(tile_dir, tileset_name, 64);
	sprintf(tile_file_name_buff, "%s/%s", tile_dir, "tload");

	if(new)
	{
		mkdir(tile_dir, 0777);
	}

	FILE *fp;

	if((fp = fopen(tile_file_name_buff, "w")) == NULL)
	{
		printw("UNABLE To Creat Tile File\n");
		return -1;
	}

	// Starts Writing
	fprintf(fp, "%s\n", ZTORG_VERSION);
	fprintf(fp, "%d\n", maxtile);

	for (int i = 0; i < maxtile; ++i)
	{
		fprintf(fp, "%s\n", tile[i].name_id);
	}

	fprintf(fp, "[MAIN>SYMB>COLO>ATTR]");

	for (int i = 0; i < maxtile; ++i)
	{
		fprintf(fp, "\n%hhd %hhd %d", tile[i].symb, tile[i].coloc, tile[i].attr);
	}


	


	fclose(fp);
	return 0;
}