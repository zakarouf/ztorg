#include "../zse/zse_all/zse_all.h"
#include <raylib3.5/raylib.h>

#ifdef Z_FREE_ROTATION
#define TURN_SPEED Z_TURN_FREELOOK
#define playermoveX(angle, spd) sinf(angle) * spd
#define playermoveY(angle, spd) cosf(angle) * spd


#else
#define TURN_SPEED Z_TURN_NORMAL
#define playermoveX(angle, spd) (int)sinf(angle) * spd
#define playermoveY(angle, spd) (int)cosf(angle) * spd

#endif 

static Color Wall_color[11] = {WHITE ,RED, GREEN, SKYBLUE, BLUE, YELLOW, DARKGRAY, BROWN, PINK, LIME, BEIGE};
static Color World_color[11] = {
	BLUE
	, BLUE
	, BLUE
	, BLUE
	, BLUE
	, BLUE
	, SKYBLUE
	, YELLOW
	, GREEN
	, DARKGREEN
	, DARKBROWN
};

static Font gDefaultFont;

//#define xy2Dto1D(x,y,X) x + ((y)*X)

#define WINDOW_X 1000
#define WINDOW_Y 600

#define CUBESIZE 2.5f

enum STAT_SHOW
{
	ST_SHOW_MINI_MAP,
	ST_SHOW_HEALTH,
	ST_SHOW_MAGE,
};

/* Data */

static int raycast_demo(ST_WORLD_t *map, Vector4 player, TILESET_t *tile)
{

	for (int x = 0; x < WINDOW_X; x++)
	{
		float ray_angle = (player.w - FOV / 2.0f) + ((float)x / (float)WINDOW_X * FOV);
		float ray_distance = 0;
		int chech_if_hitwall = 0;

		char out_of_bounds = 0;

		float p_eyeX = sinf(ray_angle);
		float p_eyeY = cosf(ray_angle);

		int point = 4;

		while (!chech_if_hitwall && ray_distance <= DEPTH && !out_of_bounds)
		{
			ray_distance += RAY_DISTANCE_INCREMENT;

			int testX = (int)(player.x+0.5f + p_eyeX * ray_distance);
			int testY = (int)(player.y+0.5f + p_eyeY * ray_distance);

			if(testX < 0 || testX >= map->Xsize || testY < 0 || testY >= map->Ysize){

				out_of_bounds = 1;
				ray_distance = DEPTH;
			}
			else {

				if(map->chunk[zse_xyz3Dto1D(testX, testY, (int)player.z , map->Xsize, map->Ysize)])
				{
					chech_if_hitwall = 1;
					point = map->chunk[zse_xyz3Dto1D(testX, testY, (int)player.z , map->Xsize, map->Ysize)];
				}
			}	
		} // WHILE LOOP END

		int ceiling = (WINDOW_Y / 2) - WINDOW_Y / (ray_distance);
		int floor = WINDOW_Y - ceiling;


		Color shade = Fade(Wall_color[point], ((ray_distance/DEPTH)-1.0f)*-1.0f);
		/*
		if(ray_distance <= DEPTH / 4 )
			shade = 0.9f;
		else if(ray_distance <= DEPTH / 3)
			shade =  0.7f;
		else if(ray_distance <= DEPTH / 2 )
			shade = 0.4f;
		else if(ray_distance <= DEPTH)
			shade = 0.1f;
		else
		{
			shade = 0.0f;
		}*/


		if (!out_of_bounds)
		{

			DrawLine(x, ceiling, x, floor, shade);
			
		}
			

	}


	return 0;
}

static void drawmap (ST_WORLD_t *map, Vector2 at, Vector3 p)
{
	int recSize = 3;
	const int minmapX = 101;
	const int minmapY = 101;

	int mapCursorx = p.x - (minmapX/recSize);
	if (mapCursorx < 0)
	{
		mapCursorx = 0;
	}

	int mapCursory = p.y - (minmapY/recSize);
	if (mapCursory < 0)
	{
		mapCursory = 0;
	}

	int mapEndx = p.x + (minmapX/recSize);
	if (mapEndx < 0)
	{
		mapEndx = map->Xsize;
	}

	int mapEndy = p.y + (minmapY/recSize);
	if (mapEndy < map->Ysize)
	{
		mapEndy = map->Ysize;
	}


	for (int i = 0 ; i < map->Ysize; ++i)
	{
		for (int j = 0 ; j < map->Xsize; ++j)
		{
			DrawRectangle(j*recSize +at.x, i*recSize +at.y, recSize, recSize, Wall_color[map->chunk[zse_xyz3Dto1D(j, i, (int)p.z, map->Xsize, map->Ysize)]]);
			mapCursorx++;
		}
		mapCursory++;
	}
	DrawRectangle((int)(at.x +p.x*recSize), (int)(at.y +p.y*recSize), recSize, recSize, BLACK);
}

static int init(void)
{
	InitWindow(WINDOW_X, WINDOW_Y, "Raytest");
	

	SetWindowState(FLAG_VSYNC_HINT);
	SetTargetFPS(60);

	//gDefaultFont = LoadFont("data/fonts/FiraCode-Regular.ttf");
	SetTextureFilter(gDefaultFont.texture, FILTER_BILINEAR);

	return 0;
}

static void ztorg_infinity(ENTT_t *p1)
{
	int recSize = 4;
	for (int i = (int)p1->Y; i < (WINDOW_Y+p1->Y)/recSize; ++i)
	{
		for (int j = (int)p1->X; j < (WINDOW_X+p1->X)/recSize; ++j)
		{
			DrawRectangle((j-p1->X) *recSize , (i-p1->Y) *recSize , recSize, recSize, World_color[(int)(zse_map_gen2d_get_solo(j, i, 0.4f, 10) *10) ]);
		}
	}
}

static void ztorg_main_loop (ENTT_t *p1, ST_WORLD_t *map, TILESET_t *tileset)
{
	// Define the camera to look into our 3d world (position, target, up vector)


	Vector3 player = {5.0f, 5.0f, 0.0f};
	const Vector3 xlr8_max = {9.0f, 9.0f, 9.0f};
	//const Vector3 xlr8_min = {1.0f, 1.0f, 1.0f};
	const Vector3 xlr8_rate = {3.2f, 3.2f, 3.2f};

	Vector3 xlr8 = xlr8_rate;

	Vector3 player_tmp = player;
	float playerA = 0.0f;
	int collision = 1;

	char msg[256];

	//Texture2D tex = LoadTexture("textures/ayy.png");
    

    // Set World Data
    // 0 is Floor
    // 1 is Wall

    Camera cam3d = {0};

    cam3d.position = (Vector3){ 4.0f, 2.0f, 4.0f };
    cam3d.target = player;
    cam3d.up = (Vector3){ 0.0f, 1.0f, 0.0f };
    cam3d.fovy = 60.0f;
    cam3d.type = CAMERA_PERSPECTIVE;

    SetCameraMode(cam3d, CAMERA_FIRST_PERSON); // Set a first person camera mode

    while(!WindowShouldClose())
    {

    	float dt = GetFrameTime();

    	// Update
        //----------------------------------------------------------------------------------
                         // Update camera
        //----------------------------------------------------------------------------------

    	player_tmp = player;

    	if (IsKeyDown(KEY_D))
    	{
    		playerA += DEGREE_1*2;
    	}

    	if (IsKeyDown(KEY_A))
    	{
    		playerA -= DEGREE_1*2;
    	}

    	if (IsKeyDown(KEY_W))
    	{

    		xlr8.x += (xlr8_rate.x + xlr8.x) * dt;
    		if (xlr8.x > xlr8_max.x)
    		{
    			xlr8.x = xlr8_max.x;
    		}

    		xlr8.y += (xlr8_rate.y + xlr8.y) * dt;

    		if (xlr8.y > xlr8_max.y)
    		{
    			xlr8.y = xlr8_max.y;
    		}

    		
    		player.x += playermoveX(playerA, (8.0f*dt)) ;
    		player.y += playermoveY(playerA, (8.0f*dt)) ;
    		if ((player.x < 0 || player.y < 0 || player.x >= map->Xsize || player.y >= map->Ysize))
    		{
				player = player_tmp;
    		}
    	}

    	if (IsKeyDown(KEY_S))
    	{

    		player.x -= playermoveX(playerA, (10.0f*dt));
    		player.y -= playermoveY(playerA, (10.0f*dt));
    		if ((player.x < 0 || player.y < 0 || player.x >= map->Xsize || player.y >= map->Ysize))
    		{
				player = player_tmp;
    		}
    	}
    	if (IsKeyPressed(KEY_E))
    	{
    		collision ^= 1;
    	}

    	if (IsKeyPressed(KEY_Z))
    	{
    		player.z = (player.z > 0)? player.z-1:player.z;
    	}
    	if (IsKeyPressed(KEY_X))
    	{
    		player.z = (player.z < map->Zsize-1)? player.z+1:player.z;
    	}


    	if (xlr8.x > 0)
    	{
    		xlr8.x -= xlr8_rate.x - xlr8.x/2 *dt;
    	}
    	if (xlr8.y > 0)
    	{
    		xlr8.y -= xlr8_rate.y - xlr8.y/2 *dt;
    	}
    	if (xlr8.x < 0)
    	{
    		xlr8.x += xlr8_rate.x + xlr8.x/2 *dt;
    	}
    	if (xlr8.y < 0)
    	{
    		xlr8.y += xlr8_rate.y + xlr8.y/2 *dt;
    	}
    	


    	if (tileset->tile[map->chunk[zse_xyz3Dto1D((int)player.x, (int)player.y, (int)player.z , map->Xsize, map->Ysize)]].attr &TILE_ISMOVE)
    	{
    		if(map->chunk[zse_xyz3Dto1D((int)(player.x + playermoveX(playerA, 1.0f)), (int)(player.y + playermoveY(playerA, 1.0f)), (int)player.z ,map->Xsize, map->Ysize)] == 0)
    		{
    			map->chunk[zse_xyz3Dto1D((int)(player.x + playermoveX(playerA, 1.0f)), (int)(player.y + playermoveY(playerA, 1.0f)), (int)player.z ,map->Xsize, map->Ysize)] = map->chunk[zse_xyz3Dto1D((int)player.x, (int)player.y, (int)player.z , map->Xsize, map->Ysize)];
    			map->chunk[zse_xyz3Dto1D((int)player.x, (int)player.y, (int)player.z , map->Xsize, map->Ysize)] = 0; 	
    		}
    	}
    	else {
    		if (tileset->tile[map->chunk[zse_xyz3Dto1D((int)player.x, (int)player.y, (int)player.z , map->Xsize, map->Ysize)]].attr &TILE_ISBLOC && collision)
    		{
    			player = player_tmp;
    		}
    		
    	}



    	sprintf(msg, "X %.2f| Y %.2f| Z %.2f| A %.2f| AX %.2f| AY %.2f| ", player.x, player.y, player.z,playerA, xlr8.x, xlr8.y);
        // Draw
        //----------------------------------------------------------------------------------
       	BeginDrawing();
		ClearBackground(BLACK);

    		raycast_demo(map, (Vector4){player.x, player.y, player.z, playerA}, tileset);
    		DrawText(msg, 10, WINDOW_Y - 15, 16, YELLOW);
    		//ztorg_infinity(p1);
    		drawmap(map, (Vector2){10, 10}, player);
			//r_3D(WORLD_DATA, cam3d);
			
    		DrawFPS(1, 1);

		EndDrawing();
        //----------------------------------------------------------------------------------

    }
}


int ztorg_ray (char name[])
{
	init();
	char *returntilesetname = malloc(ZSE_MAX_FILENAME_SIZE);

	ST_WORLD_t *map = zse_map_load_st(name , returntilesetname);
	TILESET_t tileset = zse_tileset_get(returntilesetname);

	ENTT_t *p = zse_entt_init_ENTT_t(JACK);
	p->X = 10;
	p->Y = 10;

	ztorg_main_loop (p, map, &tileset);

	zse_map_delete_st(map);
	zse_entt_delete(p);

	return 0;
}


