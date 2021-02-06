#include "sprite_lib.h"
#include "../sys/sys.h"
#include <sys/stat.h>

#define ZSE_ENABLE_COLOR


SPRITES_t zse_sprites_sin_load(char name[])
{
    SPRITES_t sprite = {0, 0, 0, 0 , 0 , NULL, NULL, NULL};

    char dirpos[74] = SPRITES_PARENTDIR;
    sprintf(dirpos, "%s%s/%s", SPRITES_PARENTDIR, name, SPRITES_SPRITE_DATAFILE);

    FILE *fp;
    if((fp = fopen(dirpos, "r")) == NULL)
    {
        return sprite;
    }

    fread(&sprite, sizeof(SPRITES_t), 1, fp);
    sprite.plot = malloc(sizeof(sprite_data_t) * sprite.X *sprite.Y * sprite.frames);
    fread(sprite.plot, sizeof(sprite_data_t) * sprite.X *sprite.Y * sprite.frames, 1, fp);

    fclose(fp);


    sprintf(dirpos, "%s%s/%s", SPRITES_PARENTDIR, name, SPRITES_SPRITE_SEQUENCE_DATAFILE);
    fp = fopen(dirpos, "w");

    sprite._seqEnd = malloc(sizeof(sequence_data_t) * sprite.seqMax);    
    fread(sprite._seqEnd, sizeof(sequence_data_t) * sprite.seqMax, 1, fp);

    #include <ncurses/ncurses.h>
    clear();
    for (int i = 0; i < sprite.seqMax; ++i)
    {
        printw("%d ", sprite._seqEnd[i]);
    }
    refresh();
    getch();

    sprite.seqData = malloc(sizeof(sequence_data_t *) * sprite.seqMax);
    for (int i = 0; i < sprite.seqMax; ++i)
    {
        sprite.seqData[i] = malloc(sizeof(sequence_data_t) * sprite._seqEnd[i]);
        fread(sprite.seqData[i], sizeof(sequence_data_t) * sprite._seqEnd[i], 1, fp);

    }

    fclose(fp);

    return sprite;

}

int zse_sprites_sin_export(SPRITES_t *sprite ,char name[])
{

    char dirpos[74] = SPRITES_PARENTDIR;

    
    sprintf(dirpos, "%s%s", SPRITES_PARENTDIR, name);
    mkdir(dirpos ,0777);

    sprintf(dirpos, "%s%s/%s", SPRITES_PARENTDIR, name, SPRITES_SPRITE_DATAFILE);

    FILE *fp;
    fp = fopen(dirpos, "w");
    if(fp == NULL)
    {
        return -1;
    }

    fwrite(sprite, sizeof(SPRITES_t), 1, fp);
    fwrite(sprite->plot, sizeof(sprite_data_t)* sprite->X * sprite->Y * sprite->frames , 1,  fp);

    sprintf(dirpos, "%s%s/%s", SPRITES_PARENTDIR, name, SPRITES_SPRITE_SEQUENCE_DATAFILE);

    fclose(fp);
    fp = fopen(dirpos, "w");


    fwrite(sprite->_seqEnd, sizeof(sequence_data_t), sprite->seqMax,fp);
    for (int i = 0; i < sprite->seqMax; ++i)
    {
        fwrite(sprite->seqData[i], sizeof(sequence_data_t) * sprite->_seqEnd[i], 1, fp);
    }

    fclose(fp);

    return 0;

}



SPRITES_t* zse_sprites_createNew(int x, int y, int frame, float dt, int sq)
{
    SPRITES_t *spr = malloc(sizeof(SPRITES_t));
    
    spr->X = x;
    spr->Y = y;
    spr->frames = frame;
    spr->dt = dt;
    spr->seqMax = sq;

    spr->plot = malloc(sizeof(sprite_data_t) * spr->X * spr->Y * spr->frames);

    for (int i = 0; i < spr->X * spr->Y * spr->frames; ++i)
    {
        spr->plot[i] = ' ';
    }

    //spr->sequences[0] = malloc(sizeof(sequence_data_t) * spr->seqMax);
    //spr->sequences[1] = malloc(sizeof(sequence_data_t) * spr->seqMax);

    return spr;
}

void zse_sprite_swapColors(SPRITES_t *spr, int targetColo, int colorCode)
{
    for (int i = 0; i < spr[0].frames*spr[0].X*spr[0].Y; ++i)
    {
        if ((spr[0].plot[i] & 0xFF00)>>8 == targetColo)
        {
            spr[0].plot[i] &= 0x00FF;
            spr[0].plot[i] |= colorCode<<8;
        }
        
    }
}


sequence_data_t** zse_sprite_malloc_sequence_data(sequence_data_t *seqEnd, int seqMax)
{
    sequence_data_t **seqData = malloc(sizeof(sequence_data_t*) * seqMax);
    for (int i = 0; i < seqMax; ++i)
    {
        seqData[i] = malloc(sizeof(sequence_data_t) * seqEnd[i]);
        memset(seqData, 0, seqEnd[i]);
    }

    return seqData;
}

void zse_sprite_deleteSpriteSequences(SPRITES_t *spr)
{
    for (int i = 0; i < spr->seqMax; ++i)
    {
        free(spr->seqData[i]);
    }
    free(spr->seqData);
    free(spr->_seqEnd);
}


void zse_delete_sprites_ptr(SPRITES_t *sprites)
{
    zse_sprite_deleteSpriteSequences(sprites);
    free(sprites);
}

void zse_delete_sprites_blocCont(SPRITES_BLOC_t spr_bloc)
{
    for (int i = 0; i < spr_bloc.blocsize; ++i)
    {
        free(spr_bloc.sprites[i].plot);
    }
    
    free(spr_bloc.sprites);
}


/*

sequence_data_t * zse_sprite_reallocSequence(int n)
{

}

SPRITES_t *zse_sprites_migrate_BlocToSpr(SPRITES_BLOC_t spr_bloc, int *return_size)
{

}
*/
