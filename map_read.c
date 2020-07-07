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

uint8_t **map_read_world (char map_name [], uint16_t *X, uint16_t *Y, uint8_t *error_n)
{
    
    if(strcmp(map_name, VACANT_MAP) == 0) {
        return NULL;
    }

    char map_dir[64] = "./maps/";
    char map_ent_buff_dir[72];
    char buffer[MAX_MAP_WIDTH];

    strncat(map_dir, map_name, 64);

    sprintf(map_ent_buff_dir, "%s/%s", map_dir, WORLD_FILE);

    // INIT FILE POINTER
    FILE *fileP;

    // LOAD MAIN MAP FILE {xy cord, map, neighbour}

    /// XY Cord

    fileP = fopen(map_ent_buff_dir, "r");

    if (fileP == NULL) {
    	error_n[0] = 1;
        return NULL;
    }

    fgets(buffer, MAX_MAP_WIDTH, fileP); // get version
    fgets(buffer, MAX_MAP_WIDTH, fileP); // get XY

    sscanf(buffer, "%hi %hi", X, Y); // Apply XY cord

    /// MAP WORLD

    uint8_t **world = malloc_2D_array_uint8 (X[0], Y[0], 0, 0);

    for (int i = 0; i < Y[0]; ++i)
    {
        for (int j = 0; j < X[0]; ++j)
        {
            fscanf(fileP, "%hhd", &world[i][j]);
        }
    }

    // ALL OK
    error_n[0] = 0;
	return world;
}