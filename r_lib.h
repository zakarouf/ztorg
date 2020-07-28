#ifndef RENDER_LIBRARY_H
#define RENDER_LIBRARY_H

#include <math.h>
#include <ncurses.h>
#include <stdint.h>

#include "map_def.h"
#include "p_def.h"
#include "e_def.h"

#include "z_config.h"

#define FOV PI_VAL/2.0f
#define DEPTH 16.0f

void r_map_2D_win (WINDOW *mini_map, PLAYER *p, MAP* m, TILE *tile, int lookdirY, int lookdirX);


void r_editor_main (EDITOR *editor, MAP *map, TILE *tile,int scrX, int scrY);
void r_render_world_raycast (PLAYER *player, MAP *map, TILE *tile);


// _______________HUD__________________
// ---EDITOR---
//void r_editor_status_hud (WINDOW *status, uint8_t stat[3], char tile_desc[][16]);

//---TMAKER---


//_______________MENU__________________

#endif