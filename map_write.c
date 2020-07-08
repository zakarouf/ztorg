/*
-----------------------------------------------------
This a Map Loading Segment
----------------------------------------------------*/

#include <string.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>

#include "alloc.h"
#include "map_lib.h"
#include "r_lib.h"

/*---------*/

int map_write_link ()
{
    return 0;
}

int map_write_world (MAP *map, char map_name[], bool new_map)
{

	char map_dir[64] = "maps/";
    char map_ent_buff_dir[72];
    //char buffer[MAX_MAP_WIDTH];

    strncat(map_dir, map_name, 64);

    if(new_map)
    {
    	mkdir(map_dir, 0777);
    }
    
    sprintf(map_ent_buff_dir, "%s/%s", map_dir, WORLD_FILE);

    // INIT FILE POINTER
    FILE *fileP;

    if((fileP = fopen(map_ent_buff_dir, "w+")) == NULL)
    {
    	fclose(fileP);
    	printw("%s", map_ent_buff_dir);
    	refresh();
    	getch();
    	return 1;
    }

    fprintf(fileP, "%s\n", MAP_VERSION_CURRENT_SIG);
    fprintf(fileP, "%hi %hi", map->X, map->Y);

    for (int i = 0; i < map->Y; ++i)
    {
    	fprintf(fileP, "\n");
        for (int j = 0; j < map->X; ++j)
        {
            fprintf(fileP, "%hhd ", map->world[i][j]);
        }
    }

    fclose(fileP);

	return 0;
}