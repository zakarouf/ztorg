#include "demo.h"

#include "../../zse/io/curses/curses.h"

#define ZSE_DEMO_INIFINIY_SCR_X 16
#define ZSE_DEMO_INIFINIY_SCR_Y 16

static uint8_t chars[10] = {' ', ' ', ' ', ' ', '.', '.', '.', '#', '#', '#'};
static uint8_t colorCode[] = {32, 32, 32, 32, 32, 33 ,185, 70, 34, 40, 28, 22, 0, 0, 0, 0, 0};

/*
static int render (IN_WORLD_t *mapIN, int playerX, int playerY, int chunkX, int chunkY)
{
    const int absXval = zse_absMapINPos(playerX, chunkX);
    const int absYval = zse_absMapINPos(playerY, chunkY);

    int startScrY = absYval - ZSE_DEMO_INIFINIY_SCR_Y;
    int startScrX = absXval - ZSE_DEMO_INIFINIY_SCR_X;

    for (int i = 0; i < ZSE_DEMO_INIFINIY_SCR_Y; ++i)
    {
        for (int j = 0; j < ZSE_DEMO_INIFINIY_SCR_X; ++j)
        {
            
        }
    }


    return 0;
}
*/

static void zse_map_InScrollChunk_Vertical3x3(IN_WORLD_t *mapIN, int ChunkX, int ChunkY, int chunklineStart, int chunklineEnd, zse_i8 incrementUP)
{
    int tmpChunksCount = 0;
    plotdata_t* tmpChunks[zse_mapInSideCLen(mapIN->_MaxChunkRadius)];



    for (int i = chunklineStart; i <= chunklineEnd; i++)
    {
        const int 
        l = (incrementUP == 0)? (i - zse_mapInSideCLen(mapIN->_MaxChunkRadius)) : (i + zse_mapInSideCLen(mapIN->_MaxChunkRadius))
        , f = (incrementUP == 0)? (i + zse_mapInSideCLen(mapIN->_MaxChunkRadius)) : (i - zse_mapInSideCLen(mapIN->_MaxChunkRadius));
        //Debug
            //mvprintw(0,0,"%d %d %d", l, f, i);
            //refresh();
            //getch();
        


        // Store first/last horizontal line pointers in tmp var
        tmpChunks[tmpChunksCount] = mapIN->chunks[l];

        // Store Previous/Next PLR Line in First/Last Horizontal line 
        mapIN->chunks[l] = mapIN->chunks[i];

        // Store Last/First Horizontal Line as New PLR
        mapIN->chunks[i] = mapIN->chunks[f];

        // Assign First/Last Horizotal Line pointers to Last Horizontal Line
        mapIN->chunks[f] = tmpChunks[tmpChunksCount];

        // Generate new Last/First Horizontal Data
        zse_map_fillupchunk_in(mapIN, f, ChunkX, ChunkY);
        ChunkX += 1 - (2*incrementUP);


        tmpChunksCount++;
    }
}

static void switchChunksVertical3x3(IN_WORLD_t *mapIN, int ChunkX, int ChunkY, zse_i8 UP)
{
    int chunklineStart
    , chunklineEnd;
    zse_mapINchunklineStartEndPLR(chunklineStart, chunklineEnd ,mapIN->_MaxChunkRadius);
    zse_map_InScrollChunk_Vertical3x3(mapIN, ChunkX, ChunkY, chunklineStart, chunklineEnd, UP);
}

static void zse_map_InScrollChunk_Horizontal3x3(IN_WORLD_t *mapIN, int ChunkX, int ChunkY, int chunklineStart, int chunklineEnd, bool increment)
{
    int tmpChunksCount = 0;
    plotdata_t* tmpChunks[zse_mapInSideCLen(mapIN->_MaxChunkRadius)];

    


}

static void switchChunksHorizontal3x3(IN_WORLD_t *mapIN, int ChunkX, int ChunkY, bool a)
{
    int chunklineStart
    , chunklineEnd;

    
    zse_map_InScrollChunk_Horizontal3x3(mapIN, ChunkX, ChunkY, chunklineStart, chunklineEnd, a);
}

static void showALLChunk(WINDOW * win, int x, int y,IN_WORLD_t * mapIN, int zlevel)
{
    
    int aty = 0;
    int atx = 0;
    for (int ChunkNo = 0; ChunkNo < zse_mapINTotalChunkNo(mapIN->_MaxChunkRadius); ++ChunkNo)
    {
        
        y = aty * mapIN->ChunkSizeXY;
        for (int i = 0; i < zse_mapINxy(mapIN); ++i)
        {
            x = atx * mapIN->ChunkSizeXY;
            for (int j = 0; j < zse_mapINxy(mapIN); ++j)
            {
                mvwaddch(win, y, x , A_REVERSE | ' ' | COLOR_PAIR(colorCode[mapIN->chunks[ChunkNo][zse_xyz3Dto1D(j, i, zlevel, zse_mapINxy(mapIN), zse_mapINxy(mapIN))]]));
                x++;
            }
            y++;

        }

        atx++;
        if ((atx % zse_mapInSideCLen(mapIN->_MaxChunkRadius)) == 0)
        {
            atx = 0;
            aty++;
        }

    }

}

static void showChunk(WINDOW * win, int x, int y, IN_WORLD_t * mapIN, int ChunkNo, int zlevel)
{
    
    for (int i = 0; i < zse_mapINxy(mapIN); ++i)
    {
        for (int j = 0; j < zse_mapINxy(mapIN); ++j)
        {

            mvwaddch(win, y, x, A_REVERSE | ' ' | COLOR_PAIR(colorCode[mapIN->chunks[ChunkNo][zse_xyz3Dto1D(j, i, zlevel, zse_mapINxy(mapIN), zse_mapINxy(mapIN))]]));
            x++;
        }
        y++;
        x = 0;
    }
}

static void showperlin(int x, int y, int Cx, int Cy, int CXYsize)
{
    for (int i = 0; i < ZSE_mapIN_CHUNK_XY_SIZE_DEFAULT*3; ++i)
    {
        for (int j = 0; j < ZSE_mapIN_CHUNK_XY_SIZE_DEFAULT*3; ++j)
        {
            mvwaddch(stdscr, j, i, A_REVERSE | ' ' | COLOR_PAIR(colorCode[(int)zse_map_gen2d_get_solo(zse_mapINAbsPos(j, Cx, CXYsize), zse_mapINAbsPos(i, Cy, CXYsize) ,0.1, 4)])*10);
        }
    }
}

int demo_perlin()
{
    int zse_map_GetNoiseSeed(void);
    void zse_map_SetNoiseSeed(int seed);
    
    IN_WORLD_t mapIN = zse_map_init_empty_in();
    ENTT_t *player = zse_entt_init_ENTT_t(JACK);

    zse_map_SetNoiseSeed(1000);
    
    player->Cx = 0;
    player->Cy = 0;
    zse_map_fillentireChunks_in(&mapIN, player->Cx - zse_mapInChunksMid(mapIN._MaxChunkRadius), player->Cy - zse_mapInChunksMid(mapIN._MaxChunkRadius));


    player->X = 0;
    player->Y = 0;

    int viewmode = 0;

    while(TRUE)
    {

        switch(getch())
        {
            case 'w':
                player->Y--;
                if(player->Y < 0)
                {
                    player->Cy--;
                    switchChunksVertical3x3(&mapIN, player->Cx, player->Cy, 0);
                    player->Y = mapIN.ChunkSizeXY-1;
                }
                break;
            case 's':
                player->Y++;
                if (player->Y >= mapIN.ChunkSizeXY)
                {
                    player->Cy++;
                    switchChunksVertical3x3(&mapIN, player->Cx, player->Cy, 1);
                    player->Y = 0;
                }
                
                break;
            case 'a':
                player->X--;
                break;
            case 'd':
                player->X++;
                break;
            case 'x':
                viewmode++;
                if (viewmode > 2)
                {
                    viewmode = 0;
                }
                break;
            case '`':
                return 0;
                break;
            default:
                break;
        }
        clear();
        move(0, 0);

        int s, e;
        zse_mapINchunklineStartEndPLR(s, e ,mapIN._MaxChunkRadius);

        if(viewmode == 1)
        {
            showChunk(stdscr, 0, 0, &mapIN, zse_mapInChunksMid(mapIN._MaxChunkRadius), 0);  
        }
        else if(viewmode == 2 )
        {
            showperlin(player->X, player->Y, player->Cx, player->Cy, mapIN.ChunkSizeXY);
        }
        else if(viewmode == 0)
        {
            showALLChunk(stdscr, 0, 0, &mapIN ,0);
        }
        //
        //
        mvprintw(getmaxy(stdscr) -3, 0, "%ld KB, Mid %d, (%d, %d) (%d, %d), Clen %d, st %d ed %d"
            , zse_sys_getRamUsage()/ 1024, zse_mapInChunksMid(mapIN._MaxChunkRadius), (int)player->X, (int)player->Y, player->Cx, player->Cy ,zse_mapInSideCLen(mapIN._MaxChunkRadius), (int)s, (int)e);
        mvprintw(player->Y, player->X, "@");
        refresh();

    }

    return 0;
}