#ifndef ZSE_SPRITES_H
#define ZSE_SPRITES_H

#include "common.h"


#include "r_colors.h"

typedef uint8_t sdata;

typedef struct SPRITES_DEF_
{
    uint16_t X;
    uint16_t Y;
    unsigned int frames;
    float fps;
    unsigned short colorused;
    COLORrgb_p *colorP;
    sdata* plot;

}SPRITES_t;

typedef struct COLORLESS_SPRITES_DEF_
{
    uint16_t X;
    uint16_t Y;
    unsigned int frames;
    float fps;
    sdata* plot;
}COLORLESS_SPRITES_t;

typedef struct SPRITES_BLOC_DEF_
{
    int blocsize;
    unsigned short colorused;
    COLORrgb_p *colorP;
    COLORLESS_SPRITES_t* sprites;

}SPRITES_BLOC_t;

#define SPRITES_PARENTDIR "sprites/"
#define SPRITES_SINGLE_EXT ".zspr"
#define SPRITES_BLOCFILE_EXT ".zbspr"

/*
    Sprite Single File Format

    [version] 8byte
    [X] uint16
    [Y] uint16
    [frames] int
    [fps] float 
    [colorused] short
    [colordata] COLORrgb_p * colorused
    [sdata] X * Y * frames
   
*/
/*
    Sprite Bloc File Format (Multiple Sprites in One File)

    [version] 8byte
    [num] int (total number of sprites)
    [name] char * MAX_FILENAME_SIZE * num
    [sprites]
*/

// Funcs
// Funcs


#endif