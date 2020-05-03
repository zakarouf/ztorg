#include <ncurses.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char const *argv[])
{

    char map_dir[52]="./maps/";                             // Directory
    char check[5];
    map1.crnt = 1;

    sprintf(map1.name, "%s", map_name);


    strcat(map_dir, map1.name);
    FILE *map_file;
    map_file = fopen(map_dir, "r");

    if (map_file == NULL) {
        printw("Map Doesnt Exist");
        return -1;
    }

    return 0;
	return 0;
}