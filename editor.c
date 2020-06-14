/*
-----------------------------------------------------
All Editor Realated function
-----------------------------------------------------
draw_box - Draws a Box w/o filling it
fillup_box - Draws a Box w/ filling
draw_circle - Draws a Box w/o filling
fillup_circle - Draws a Box w/ filling

-----------------------------------------------------*/
#include <ncurses.h>
#include "map.h"
#include "map_load.h"
#include "g_main.h"

void save_map (int link_count) {
    map_export(link_count);
}

int add_map_linker (int x, int y, char name[54], int linkcount) {

    sprintf(mapED.linkname[linkcount], "%s", name);
    mapED.link[linkcount][0] = x;
    mapED.link[linkcount][1] = y;
    mapED.world[y][x] = '^';
    mapED.crnt = 0;

    clear();
    process_map_file(mapED.linkname[linkcount]);
    for (int i = 0; i < map1.Y; ++i)
    {
        printw("%s", map1.world[i]);
    }
    getch();
    g_normal(0, 0, 1);
    link_add_enx (mapED.linkname[linkcount], mapED.link[linkcount][2], mapED.link[linkcount][3], x, y);

    mapED.crnt = 1;
    map1.crnt = 0;
    linkcount++;

    noecho();

    return linkcount;
}

void draw_box (int x, int y, int ex, int ey ,char c) {
    int i, j;
    for (i = 0; i < mapED.Y; ++i) {
        for (j = 0; j < mapED.X; ++j) {

            if((i == ey || i == y || j == ex || j == x) && ((ex <= j && j <= x) && (ey <= i && i <= y))){
                mapED.world[i][j] = c;
            }
        }
    }
}

void fillup_box (int x, int y, int ex, int ey, char c) {
	int i, j;
    for (i = 0; i < mapED.Y; ++i) {
        for (j = 0; j < mapED.X; ++j) {

            if((ex <= j && j <= x) && (ey <= i && i <= y)) {
                mapED.world[i][j] = c;
            }
        }
    }
}


void draw_circle (int x, int y, char c) {
    int i, j, r;
    scanw("%d", &r);

    // NOTE: This is fucking retarded, function is checking all points of the map array.
	// 		 Make a Cube. Please
	
    for (i = 0; i < mapED.Y; ++i) {
        for (j = 0; j < mapED.X; ++j) {

            if( ((j - x) * (j - x) + (i - y) * (i - y)) >= r * r) {
                mapED.world[i][j] = c;
            }
        }
    }
}

// Draw & Fill Circle
void fillup_circle (int x, int y, int r ,char c) {

    for (int i = y - r; i < y + r + 1; ++i) {
        for (int j = x - r; j < x + r + 1 ; ++j) {

            if( ((j - x) * (j - x) + (i - y) * (i - y)) <= r * r ) {
                mapED.world[i][j] = c;
            }
        }
    }
}