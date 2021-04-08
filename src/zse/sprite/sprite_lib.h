#ifndef ZSE_SPRITES_OLD_H
#define ZSE_SPRITES_OLD_H

#include "../common.h"

typedef uint16_t sprite_data_t;
typedef uint16_t sequence_data_t;

typedef struct SPRITES_DEF_
{
    uint16_t X;
    uint16_t Y;
    uint16_t frames;
    float dt;
    uint16_t seqMax;


    sprite_data_t* plot;
    sequence_data_t* _seqEnd; // Sequence End
    sequence_data_t** seqData;
    

// for (int i = 0; i < seqSE[SeqNum]; ++i)
// {
//      seq[Seqnum][i];    
// }


}SPRITES_t;

typedef struct SEQUENCELESS_SPRITES_DEF_
{
    uint16_t X;
    uint16_t Y;
    unsigned int frames;
    float dt;
    sprite_data_t* plot;
}SEQUENCELESS_SPRITES_t;

typedef struct SPRITES_BLOC_DEF_
{
    int blocsize;
    //COLORrgb_p *colorP;
    SEQUENCELESS_SPRITES_t* sprites;

}SPRITES_BLOC_t;

#define SPRITES_PARENTDIR "sprites/"

#define SPRITES_SPRITE_DATAFILE "sprdata.bin"
#define SPRITES_SPRITE_SEQUENCE_DATAFILE "seqdata.bin"
#define SPRITES_SINGLE_EXT ".zspr"
#define SPRITES_SEQUENCE_EXT ".zssq"
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

SPRITES_t* zse_sprites_createNew(int x, int y, int frame, float dt, int sq);
void zse_delete_sprites_ptr(SPRITES_t *sprites);

void zse_sprite_swapColors(SPRITES_t *spr, int targetColo, int colorCode);

sequence_data_t** zse_sprite_malloc_sequence_data(sequence_data_t *seqEnd, int seqMax);

#endif

