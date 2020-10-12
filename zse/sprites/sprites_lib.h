#ifndef ZSE_SPRITES_H
#define ZSE_SPRITES_H

#include "../common.h"


#include "../colors/colors.h"

typedef uint16_t sprite_data_t;

typedef struct SPRITES_DEF_
{
    uint16_t X;
    uint16_t Y;
    unsigned int frames;
    float dt;
    unsigned short colorused;
    sprite_data_t* plot;
    COLORrgb_p *colorP;

}SPRITES_t;

typedef struct COLORLESS_SPRITES_DEF_
{
    uint16_t X;
    uint16_t Y;
    unsigned int frames;
    float dt;
    sprite_data_t* plot;
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

#define zse_sprX(spr) (SPRITES_t)spr.X
#define zse_sprY(spr) (SPRITES_t)spr.Y

// Funcs
SPRITES_t zse_sprites_sin_load(char name[]);
int zse_sprites_sin_export(SPRITES_t *sprite ,char name[]);

void zse_delete_sprites_ptr(SPRITES_t *sprites, size_t siz);

#endif