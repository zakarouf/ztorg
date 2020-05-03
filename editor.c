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
    int i, j, r, f;
    mvscanw(mapED.Y+6,0,"%d", &r);
    f = r-1;
    for (i = 0; i < mapED.Y; ++i) {
        for (j = 0; j < mapED.X; ++j) {

            if( ((j - x) * (j - x) + (i - y) * (i - y)) <= r * r && ((j - x) * (j - x) + (i - y) * (i - y)) >= f * f ) {
                mapED.world[i][j] = c;
            }
        }
    }
}

// Draw & Fill Circle
void fillup_circle (int x, int y, char c) {
    int i, j, r;
    mvscanw(mapED.Y+6,0,"%d", &r);
    for (i = 0; i < mapED.Y; ++i) {
        for (j = 0; j < mapED.X; ++j) {

            if( ((j - x) * (j - x) + (i - y) * (i - y)) <= r * r) {
                mapED.world[i][j] = c;
            }
        }
    }
}