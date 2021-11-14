#include "zse/map/ch.h"
#include "zse/zse_all/zse_all.h"
#include "zse/entity/actor.h"
#undef KEY_END
#undef KEY_HOME
#undef KEY_LEFT
#undef KEY_UP
#undef KEY_DOWN
#undef KEY_RIGHT
#undef KEY_BACKSPACE
#undef KEY_ENTER
#include "./zse/io/raylib/raygui.h"
#include "./zse/map/ch_fio.h"
#include <stdlib.h>

#include <z_/types/string.h>
#include <z_/types/autotype.h>

#define WINDOW_X 1000
#define WINDOW_Y 600

z__Record(
	Plot	
	, (z__u8, plot)
	, (z__u16, texID)
	, (z__f32, oriantaion)
	, (z__u8, flags)
);

typedef
	zse_T_MapCh(record Plot) Map;



static int _init(void)
{
	InitWindow(WINDOW_X, WINDOW_Y, "Raytest");
	

	SetWindowState(FLAG_VSYNC_HINT);
	SetTargetFPS(60);

	//gDefaultFont = LoadFont("data/fonts/FiraCode-Regular.ttf");
	//SetTextureFilter(gDefaultFont.texture, FILTER_BILINEAR);

	return 0;
}

void mainloop(void)
{
	Map map;
	zse_map_ch_createEmpty(&map, 32, 32, 2, 0);

	while(!WindowShouldClose()) {
		
	}
}

void rpg(void)
{
    _init();
	mainloop();
	CloseWindow();
}

/*

void draw_tex(Texture tx, Vector2 tilesz, Vector2 tile, float rotation, float scale) {

	z__auto x = tilesz.x;
	z__auto y = tilesz.y;
	const Rectangle source = {
		.x = x * tile.x,
		.y = y * tile.y,
		.width = x,
		.height = y
	},
	
	dest = {
		.width = x * scale,
		.height = y * scale,
		.x = 0,
		.y = 0
	};


	DrawTextureTiled(tx, source, dest, (Vector2){0}, rotation, scale, WHITE);
}

void draw_map(zse_T_MapCh *map, Texture tx, Texture cur,float scale) {
	const float x = 16, y = 16;
	Rectangle source = {
		.x = x,
		.y = 0,
		.width = x,
		.height = y
	},
	
	dest = {
		.width = x * scale,
		.height = y * scale,
		.x = 0,
		.y = 0
	};

	for(int i = 0; i < map->size.y; i++) {
		for(int j = 0; j < map->size.x; j++) {
			dest.x = j * 16;
			dest.y = i * 16;

			source.x = ZSE_map__CH_getraw(map, j, i, 0, 0).plot * x;
			DrawTextureTiled(tx, source, dest, (Vector2){0}, 0, scale, WHITE);
		}
	}
}



void gameloop()
{
	zse_T_MapCh *map = z__New(*map, 1);
	zse_map_ch_createEmpty(map, 32, 32, 2, 0);

	for(int i = 0; i < map->size.y; i++) {
		for(int j = 0; j < map->size.x; j++) {
			ZSE_map__CH_getraw(map, j, i, 0, 0).plot = (int)(zse_map__genP2d_getSolo(j, i, 0.1, 10) * 10) % 4;
		}
	}

	Texture tile_tex = LoadTexture("textures/MWS/Ground/Grass.png");
	Texture cursor = LoadTexture("textures/MWS/UserInterface/BoxSelector.png");

	Vector2 tile_hw = {16, 16};
	int text_count = (tile_tex.height /16) * (tile_tex.width / 16);



//	z__Arr(Vector2) textures;
//	z__Arr_new(&textures, text_count);

	Vector2 pos = {0, 0};


	z__Vint2 tile = {0, 0};

	while(!WindowShouldClose()) {

		z__f32 dt = GetFrameTime();

		z__auto key = GetKeyPressed();
		
		switch(key){
			
		}

		BeginDrawing();
			ClearBackground(BLACK);
			
			//draw_tex(tile_tex, tile_hw, (Vector2) {0, 0}, (Vector2) {0, 32}, 1);
			//draw_tex(tile_tex, tile_hw, (Vector2) {1, 0}, (Vector2) {32, 32}, 1);
			//draw_tex(tile_tex, tile_hw, (Vector2) {2, 0}, (Vector2) {0, 64}, 1);
			//draw_tex(tile_tex, tile_hw, (Vector2) {3, 0}, (Vector2) {0, 96}, 1);

			//DrawTextureTiled(tile_tex, source, dest, pos, rotation, scale, WHITE);
			//DrawTextureRec(tile_tex, tile_source, pos, WHITE);
			//

			//draw_tex(tile_tex, (Vector2){16, 16}, (Vector2){0, 0}, 0, 1);
			
			draw_map(map, tile_tex, cursor, 1);
			
		EndDrawing();
	}
}

#include <string.h>

#define ZSE_OK 1
#define ZSE_ERR 0

typedef
	struct {
		struct {
			z__Vector(z__u32, p, q, r) *points;
			z__Vector(z__u32, qp, pr, rq) *neighbours;
		} sectors;
		zse_T_Map_ObjectArr *objectSets;
		z__size count;
} zse_T_MapSector;

*/


struct Tile {
	z__u16 tile_id;
	z__u8 texture_id;

	z__f32 oriantaion;
	z__u8 flags;
};

typedef zse_T_MapCh(struct Tile) MapType;

/*
 *
 */

void rpgoi(void)
{
	MapType map;
	z__Arr(z__Vector2) enemypos;

	// Create an empty map with 10x10x1 dimention.
	zse_map_ch_createEmpty(&map, 10, 10, 1, 0);
	
	// Set some map points
	map.chunks[0][4].tile_id = 23;
	map.chunks[0][63].tile_id = 1;
	map.chunks[0][13].tile_id = 8;
	map.chunks[0][99].tile_id = 90;

	z__Arr_new(&enemypos, 10);

	z__Arr_push(&enemypos, (z__Vector2){{32, 65}});
	z__Arr_push(&enemypos, (z__Vector2){{2, 99}});
	z__Arr_push(&enemypos, (z__Vector2){{23, 52}});
	z__Arr_push(&enemypos, (z__Vector2){{52.02f, 9.21}});
	z__Arr_push(&enemypos, (z__Vector2){{92.2, 77.1}});

	zse_map_ch_obj_push(&map, 0, enemypos.data, sizeof(*enemypos.data), enemypos.lenUsed, 8);
	zse_map_ch_obj_push(&map, 0, enemypos.data, sizeof(*enemypos.data), enemypos.lenUsed, 8);
	zse_map_ch_obj_push(&map, 0, enemypos.data, sizeof(*enemypos.data), enemypos.lenUsed, 8);
	zse_map_ch_obj_push(&map, 0, enemypos.data, sizeof(*enemypos.data), enemypos.lenUsed, 8);

	// Write map data on disk
	zse_map_ch_export_st(&map, "kk", 0, true);

	zse_map_ch_delete(&map);
	z__Arr_delete(&enemypos);

	/*----------------------*/

	MapType newmap;
	z__Arr(z__Vector2) enemypos_new;

	// Load Map data from disk
	zse_map_ch_load_st(&newmap, "kk");

	// Show Map data;
	for(int i = 0; i < 100; i++){
		printf("%i %hu\n", i, newmap.chunks[0][i].tile_id);
	}

	enemypos_new.data = newmap.objectSets->data->data;
	enemypos_new.len = newmap.objectSets->data->lenUsed;

	for(int i = 0; i < enemypos_new.len; i++) {
		printf("%f, %f\n", enemypos_new.data[i].x, enemypos_new.data[i].y);
	}

	zse_map_ch_delete(&newmap);
	z__Arr_delete(&enemypos_new);

    //_init();
	//gameloop();
	//CloseWindow();
}

