#ifndef MAP_LOAD_H
#define MAP_LOAD_H

void map_export (int link_count);

void link_add_enx (char map_name[32], int x, int y, int ex, int ey);

void map_autogen ();

int process_map_file_ED (char map_name[54]);
int process_map_file (char map_name[54]);

#endif