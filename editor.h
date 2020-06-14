#ifndef EDITOR_H
#define EDITOR_H

void save_map (int link_count);
int add_map_linker (int x, int y, char name[54], int linkcount);

void draw_circle (int x, int y, char c);
void fillup_circle (int x, int y, int r, char c);

void draw_box (int x, int y, int ex, int ey ,char c);
void fillup_box (int x, int y, int ex, int ey, char c);

#endif