#ifndef RENDER_H
#define RENDER_H

#include <ncurses.h>

void render_scr ();
void render_scr_ED (int x, int y);
void render_scr_fin (int px, int py);
void render_scr_fin_ED (int px, int py);
//void render_scr_win_ED ();

void raycasting_test (float playerX, float playerY, float playerA, int scrWIDTH,int scrHEIGHT);

#define SCREEN_X 25
#define SCREEN_Y 25

#define PI_VAL 3.14159265f
#define FOV PI_VAL/2.0f
#define DEPTH 16.0f

#endif