#ifndef ZAKAROUF_ZSE__MAP_CHUNKTYPE_DEFINATIONS_H
#define ZAKAROUF_ZSE__MAP_CHUNKTYPE_DEFINATIONS_H

#include "../common.h"
#include <z_/types/dynt.h>
#include <z_/types/record.h>

#include "obj_def.h"

/* Main Header For Chunk Defination. */

/* Pre-requisite:
 * 1. We Are Assuming that the Chunks Are always laid in Square Formation, No Circle or Renctangle
 * 2. The Player Chunk; The Chunk the player is on, is always in the middle in the formation
 * 3. Side of our square formation is always a odd number.
 * 4. The Total Count of the Chunks will be determined by a `Radius` from the Player going outwards in each direction.
 */

/*  . . . . . 
 *  . . . . . <- Each . is a chunk of (ChunkSizeXY * ChunkSizeXY) * ChunkSizeZ
 *  . . @ . .  - @ is the chunk inhabitate by the player
 *  . . . . .  - Chunk Size is 2 here
 *  . . . . . 
 *
 *   /---------/
 *      . . .
 *      . @ . <- Chunk No. Size = 1 (DEFAULT) _MaxChunk
 *      . . .
 *
 *   /---------/
 *
 *    . . . . . . .
 *    . . . . . . .
 *    . . . . . . .
 *    . . . @ . . . 	<- Radius Set to 3, Side = 7, Total = 7*7 = 49
 *    . . . . . . .
 *    . . . . . . .
 *    . . . . . . .
 *
 */

/*
 *    Chunk Side Length Increase by 2 per Radius :-
 *        3, 5, 7, 9
 *        ^  ^  ^  ^
 *        1, 2, 3, 4 
 *        
 *        Chunkside(r) = (1 + 2*r)
 *
 *    And The Total Number of Chunk Will Always be square of side:
 *
 *		Chunks(r) = Chunkside(r)^2 
 *
 *    /-----------------------------------------/
 *  Chunk Mid Point :-
 *      1 5 13 
 *
 *      ChunksMid(r) = (int)( (float)(Chunks(r)/2) + 0.5f )
 *
 *  Chunk lastline First Point :-
 *
 */

/*    Chunks File Naming Scheme :-
 *		Cx,Cy,Cz.bin
 *		|  |  |
 *		|  |  |- `z` Chunk z cordinate
 *		|  |- `y` Chunk y cordinate
 *		|- `x` Chunk x cordinate
 *
 *      #EXECUTABLE DIR
 *        |- maps
 *          |- #MAP NAME
 *            |- MAP_COMMON_DATA  <== Stores Map size, attributes et cetera.
 *            |- CHUNK CORD (eg. 1,1,1.bin
 *                               -1,1,0.bin)
 *
 *
 */

/*------------------------------------------------------------------------------*/
/*---------------------------------------Types----------------------------------*/

/*----------MapPlot----------*/
typedef 
    struct {
        // Main data
        z__u8 plot;

        // Texture ID;
        z__u16 texID;
        z__f32 oriantaion;

        // Attributes/Flags
        z__u8 flags;
} zse_T_MapCh_Plot;




/*----------MapType------------*/

/**
 * zse_T_MapCh()
 * Tileset Oriented Map Type with layers or z-dimention. and Multiple Chunks.
 * size: Dimention of Each Chunk.
 * chunkCount: Total no. of chunks allocated.
 * chunkRadius: Radius of square-grid layout of chunks.
 */
#define zse_T_MapCh(T, ...)\
    struct { \
        /* Map Size in x, y, z  */                                                      \
        z__Vint3 size;                                                                  \
                                                                                        \
        /* Total no. chunks allocated */                                                \
        z__size chunkCount;                                                             \
        /*Radius of square-grid layout of chunks. f(n) = ceil(2/n) - 1*/                \
        z__u16 chunkRadius;                                                             \
                                                                                        \
        /**
         * Main Data Stream
         * * Of each point of 4D array normalized to 2D array (3D each)
         * * The actual way it is being internalized is Described obove although
         *   anyone is free change it.
         */                                                                             \
        T **chunks;                                                                     \
                                                                                        \
        /**
         * Misc Map Objects.
         * Can Contain: 
         *  * Entities,
         *  * Non Static Tile Objects,
         *  * Anything Else.
         * NOTE: This does not parse any any data, Only stores them for later use.
         * NOTE: objectSet[chunk][obj];
         * NOTE: Objects of the same type are stored side-by-side.
         */                                                                 \
        zse_T_Map_ObjectSetsArr *objectSets;                                \
                                                                            \
        /**
         * Extra Stuff Declared later on (Optional)
         * NOTE Initialization & Deletion of any heap data of the vars declared
         *      here is upto the one who declared it in the first place as this module
         *      can't predict the declaration beforehand.
         */                                                         \
        __VA_ARGS__;                                                \
    }



#define ZSE_map__CH_DEFAULT_RADIUS_SIZE 1
#define ZSE_map__CH_DEFAULT_X_SIZE 		32
#define ZSE_map__CH_DEFAULT_Y_SIZE 		32
#define ZSE_map__CH_DEFAULT_Z_SIZE 		16


#define ZSE_map_ch_size(map)        (map)->size
#define ZSE_map_ch_xsize(map)       (map)->size.x
#define ZSE_map_ch_ysize(map)       (map)->size.y
#define ZSE_map_ch_zsize(map)       (map)->size.z

#define ZSE_map_ch_chunkCount(map)  (map)->chunkCount
#define ZSE_map_ch_chunkRadius(map) (map)->chunkRadius



#define ZSE_map_ch_get(map, x1, y1, z1, ch_x, ch_y, ch_z)\
    ((map)->chunks\
        [zse_xyz3Dto1D(ch_x, ch_y, ch_z, ZSE_map_ch_calcChunk_Side_fromRad(map), ZSE_map_ch_calcChunk_Side_fromRad(map))]\
            [zse_xyz3Dto1D(x1, y1, z1, (map)->size.x, (map)->size.y)])

#define ZSE_map_ch_getraw(map, x1, y1, z1, ch_num)\
    ((map)->chunks\
        [ch_num]\
            [zse_xyz3Dto1D(x1, y1, z1, (map)->size.x, (map)->size.y)])


/* (p == playerCord|xyz|, C == chunkCord|xyz|, CSize == chunkSize|xyz|) */ 
#define ZSE_map_ch_calcAbsPos(p, C, CSize) (((CSize)*(C)) + p)


#define ZSE_map_ch_calcChunk_Side_fromRad(map)   (1 + (2 * ((map)->chunkRadius)))
#define ZSE_map_ch_calcChunk_Count_fromRad(map)\
    ZSE_map_ch_calcChunk_Side_fromRad(map) * ZSE_map_ch_calcChunk_Side_fromRad(map)

#define ZSE_map_ch_calcChunk_Mid_fromRad(map)    (z__int)( ((z__float)ZSE_map_ch_calcChunk_Count_fromRad(map) /2) - 0.5f )

#define ZSE_map_ch_calcChunk_Side_fromRad__num(radius)   (1 + (2 * (radius)))
#define ZSE_map_ch_calcChunk_Count_fromRad__num(radius)  ZSE_map_ch_calcChunk_Side_fromRad__num(radius) * ZSE_map_ch_calcChunk_Side_fromRad__num(radius)
#define ZSE_map_ch_calcChunk_Mid_fromRad__num(radius)    (z__int)( ((z__float)ZSE_map_ch_calcChunk_Count_fromRad__num(radius) /2) - 0.5f )

#define ZSE_map_ch_setChunk_Count_fromRad(map)   { (map)->chunkCount = ZSE_map_ch_calcChunk_Count_fromRad(map) }
#define ZSE_map_ch_evalChunk_Count_fromRad(map)  ((map)->chunkCount == ZSE_map_ch_calcChunk_Count_fromRad(map)? true: false)


/* ----------------------------------------- *** ----------------------------------------- */
/* ----------------------------------------- *** ----------------------------------------- */

#endif
