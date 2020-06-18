#ifndef RENDER_H
#define RENDER_H

#include <ncurses.h>

void render_scr_fin (int px, int py, int render_lim__Y, int render_lim__X);
void render_scr_fin_ED (int px, int py, int scrX, int scrY);

// Raycasting Mode
void raycasting_test (float playerX, float playerY, float playerA, int scrWIDTH,int scrHEIGHT);


#define PI_VAL     3.1415926535f   // Also 180 DEGREE
#define DEGREE_90  PI_VAL/2.0f
#define DEGREE_270 3.0f*PI_VAL/2.0f
#define DEGREE_1   0.0174533f

#define FOV PI_VAL/2.0f
#define DEPTH 16.0f

#endif