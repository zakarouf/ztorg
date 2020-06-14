/*
-----------------------------------------------------
This a Map Loading Segment
----------------------------------------------------*/

#include "map.h"
#include "map_load.h"
#include <string.h>
#include <stdint.h>
#include <stdio.h>
#include <ncurses.h>

/*
---------------------------------------------------------------------
MAP SUPPORTED VERSION AND SIGNATURE

IT refers to the current supported version of MAP

IT remains the same until a new MAP LOADER build makes it unable
to load legacy map files in which case A new Version Will be set
corresponding to the Relative Game Version.

---------------------------------------------------------------------*/
#define MAP_VERSION_CURRENT_SIG "0.2f"
#define MAP_VERSION_SUPPORT_SIG "0.2f"
/*-------------------------------------------------------------------*/

/*
---------------------------------------------------------------------
MAP CONFIG LOADER
---------------------------------------------------------------------*/
#define LINK_START "LINK/START"
#define LINK_END "LINK/END"
#define NEIGHBOUR "NEIGHBOUR"
#define VACANT_MAP "VACANT_M_1"
/*---------------------------------------------------------------------*/

void make_map_mask ();

void map_export (int link_count) {

	clear();
	echo();
    printw("WAT");
    
    char map_dir[52]="./maps/";                             // Directory
    int i;
    char buffer[MAX_MAP_WIDTH+1];

    strcat(map_dir, mapED.name);


    FILE *map_File;
    map_File = fopen(map_dir, "w");


	fputs(MAP_VERSION_SUPPORT_SIG, map_File);
	sprintf(buffer, "\n%d %d\n", mapED.X, mapED.Y);
    fputs(buffer, map_File);

    for (i = 0; i < mapED.Y; i++) {
    	fputs(mapED.world[i], map_File);
        fputs("\n", map_File);
    }

    fputs(NEIGHBOUR, map_File);
    fputc('\n', map_File);

    clear();
    printw("PLEASE ENTER NEIGHBOUR NAME (if 0 then it wll not be added)\nN\nS\nE\nW\n");

    for (i = 0; i < 4; ++i)
    {
        move(i+1, 1);
    	printw(" -> ");
    	scanw("%s", buffer);
        if (strcmp("0", buffer) == 0)
        {
            fputs(VACANT_MAP, map_File);
        }
    	else{fputs(buffer, map_File);}
    	if(i != 3){fputc(' ', map_File);}
    }
    

    clear();
    fputc('\n', map_File);
    fputs(LINK_START, map_File);
    for (i = 0; i < link_count; ++i)
    {	
    	sprintf(buffer, "\n%s %d %d %d %d", mapED.linkname[i], mapED.link[i][0], mapED.link[i][1], mapED.link[i][2], mapED.link[i][3]);
    	fputs(buffer, map_File);
    }

    for (i = 0; i < link_count; ++i)
    {
    	printw("\n%s %d %d %d %d\n", mapED.linkname[i], mapED.link[i][0], mapED.link[i][1], mapED.link[i][2], mapED.link[i][3]);
    }
    printw("%d", link_count);

    fclose(map_File);
    
    printw("\nMAP SAVED");
    getch();
}

void link_add_enx (char map_name[32], int x, int y, int ex, int ey) {
    char map_dir[52]="./maps/";

    strcat(map_dir, map_name);

    FILE *map_file;
    map_file = fopen(map_dir, "a");
    fprintf(map_file, "\n%s %d %d %d %d", mapED.name, x, y, ex, ey);

    fclose(map_file);
}


void map_autogen ()
{
	clear();
	echo();
    printw("Enter Map Size\nX : ");
    scanw("%i", &mapED.X);
    printw("Y : ");
    scanw("%i", &mapED.Y);
    printw("Map Name : ");scanw("%s", mapED.name);

    for (int i = 0; i < mapED.Y; ++i)
    {   
        for (int j = 0; j < mapED.X; ++j)
        {
        	mapED.world[i][j]=' ';
        }
    }
    mapED.crnt = 1;
    make_map_mask ();
}

int process_map_file_ED (char map_name[54]) {
    if(strcmp(map_name, VACANT_MAP) == 0) {
        return 2;
    }

    char map_dir[52]="./maps/";                             // MAP Directory
    char buffer[MAX_MAP_WIDTH];
    mapED.crnt = 1;

    sprintf(mapED.name, "%s", map_name);


    strcat(map_dir, mapED.name);
    FILE *map_file;
    map_file = fopen(map_dir, "r");

    if (map_file == NULL) {
        printw("Map Doesnt Exist");
        return -1;
    }

    fgets(buffer, MAX_MAP_WIDTH, map_file);
    fgets(buffer, MAX_MAP_WIDTH, map_file);
    sscanf(buffer, "%d %d", &mapED.X, &mapED.Y);

    for (int i = 0; i < mapED.Y; ++i)
    {
        fgets(mapED.world[i], MAX_MAP_WIDTH, map_file);
    }

    fgets(buffer, MAX_MAP_WIDTH, map_file);
    
        fgets(buffer, MAX_MAP_WIDTH, map_file);
             //    north south east west
             //       \     |   /   / 
             //        \    |  |   /
             //         \   |  |  /
        sscanf(buffer, "%s %s %s %s", mapED.neighbour[0], mapED.neighbour[1], mapED.neighbour[2], mapED.neighbour[3]);

   
    // Linkers
    fgets(buffer, MAX_MAP_WIDTH, map_file);

        int count=0;
        while(1){
            
            if (fgets (buffer, MAX_MAP_WIDTH, map_file)!=NULL )
            {
                //fgets(buffer, MAX_MAP_WIDTH, map_file);                  //player X   //player Y     //goto y       //goto y
                sscanf(buffer, "%s %d %d %d %d", mapED.linkname[count], &mapED.link[count][0], &mapED.link[count][1], &mapED.link[count][2], &mapED.link[count][3]);
            }
            else{break;}
            count++;
        }
    fclose(map_file);
    make_map_mask ();

    return 0;
}

int process_map_file (char map_name[54]) {
    if(strcmp(map_name, VACANT_MAP) == 0) {
        return 2;
    }

    char map_dir[52]="./maps/";                             // MAP Directory
    char buffer[MAX_MAP_WIDTH];
    map1.crnt = 1;

    sprintf(map1.name, "%s", map_name);


    strcat(map_dir, map1.name);
    FILE *map_file;
    map_file = fopen(map_dir, "r");

    if (map_file == NULL) {
        printw("Map Doesnt Exist");
        return -1;
    }

    fgets(buffer, MAX_MAP_WIDTH, map_file);
    fgets(buffer, MAX_MAP_WIDTH, map_file);
    sscanf(buffer, "%d %d", &map1.X, &map1.Y);

    for (int i = 0; i < map1.Y; ++i)
    {
        fgets(map1.world[i], MAX_MAP_WIDTH, map_file);
    }

    fgets(buffer, MAX_MAP_WIDTH, map_file);
    
        fgets(buffer, MAX_MAP_WIDTH, map_file);
             //    north south east west
             //       \     |   /   / 
             //        \    |  |   /
             //         \   |  |  /
        sscanf(buffer, "%s %s %s %s", map1.neighbour[DIRECTION_NORTH], map1.neighbour[DIRECTION_SOUTH], map1.neighbour[DIRECTION_EAST], map1.neighbour[DIRECTION_WEST]);

   
    // Linkers
    fgets(buffer, MAX_MAP_WIDTH, map_file);

        int count=0;
        while(1){
            
            if (fgets (buffer, MAX_MAP_WIDTH, map_file)!=NULL )
            {
                //fgets(buffer, MAX_MAP_WIDTH, map_file);                  //player X 	//player Y 	   //goto y 	  //goto y
                sscanf(buffer, "%s %d %d %d %d", map1.linkname[count], &map1.link[count][0], &map1.link[count][1], &map1.link[count][2], &map1.link[count][3]);
            }
            else{break;}
            count++;
        }
    fclose(map_file);
    make_map_mask ();

    return 0;
}

void make_map_mask () {
    for (int i = 0; i < MAX_MAP_HEIGHT; i++) {
        for (int j = 0; j < MAX_MAP_WIDTH; ++j)
        {
            mask[i][j]=' ';
        }
    }
}
