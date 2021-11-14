#if 0
#include "../../zse/zse_all/zse_all.h"
#include "../../zse/entity/actor.h"
#undef KEY_END
#undef KEY_HOME
#undef KEY_LEFT
#undef KEY_UP
#undef KEY_DOWN
#undef KEY_RIGHT
#undef KEY_BACKSPACE
#undef KEY_ENTER
#include <raylib3.5/raylib.h>
#include <stdlib.h>

#include <z_/types/string.h>
#include <z_/types/autotype.h>

#define WINDOW_X 1000
#define WINDOW_Y 600

static int _init(void)
{
	InitWindow(WINDOW_X, WINDOW_Y, "Raytest");
	

	SetWindowState(FLAG_VSYNC_HINT);
	SetTargetFPS(60);

	//gDefaultFont = LoadFont("data/fonts/FiraCode-Regular.ttf");
//	SetTextureFilter(gDefaultFont.texture, FILTER_BILINEAR);

	return 0;
}

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

void dra_map(zse_T_MapCh *map, Texture tx, Texture cur,float scale) {
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

			source.x = ZSE_map__CH_getraw(map, j, i, 0, 0).tile * x;
			DrawTextureTiled(tx, source, dest, (Vector2){0}, 0, scale, WHITE);
		}
	}
}

void loadfile(void)
{
    
}

void gameloop()
{


	Texture tile_tex = LoadTexture("textures/MWS/Ground/Grass.png");
	Texture cursor = LoadTexture("textures/MWS/UserInterface/BoxSelector.png");

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
			
			
		EndDrawing();
	}
}



void rpg(void)
{
    _init();
	gameloop();
	CloseWindow();
}

#endif
