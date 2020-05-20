#ifndef RENDER_H
#define RENDER_H

#include <ncurses.h>

void render_scr ();
void render_scr_ED (int x, int y);
void render_scr_fin (int px, int py);
void render_scr_fin_ED (int px, int py);
//void render_scr_win_ED ();

#define SCREEN_X 31
#define SCREEN_Y 25


#endif