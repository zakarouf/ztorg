#include "sprite_lib.h"
#include "../sys/sys.h"

#define ZSE_ENABLE_COLOR

SPRITES_t zse_sprites_sin_load(char name[])
{
	SPRITES_t sprite = {0, 0, 0, 0 ,0, NULL, {NULL, NULL}};

	char dirpos[74] = SPRITES_PARENTDIR;
	sprintf(dirpos, "%s%s", SPRITES_PARENTDIR, name);

	FILE *fp;
	if((fp = fopen(dirpos, "r")) == NULL)
	{
		return sprite;
	}

	// Read Stuff
	char version[8];
	fread(version, sizeof(char) *8, 1, fp);
	//zse_sys_formatCheck(version);

	fread(&sprite, sizeof(SPRITES_t), 1, fp);
	
	sprite.plot = malloc(sizeof(sprite_data_t) * sprite.X * sprite.Y * sprite.frames);
	fread(sprite.plot, sizeof(sprite_data_t), sprite.X * sprite.Y * sprite.frames, fp);


	sprite.sequences[0] = malloc(sizeof(sequence_data_t) * sprite.seqMax);
	sprite.sequences[1] = malloc(sizeof(sequence_data_t) * sprite.seqMax);


	fread(sprite.sequences[0], sizeof(sequence_data_t) *sprite.seqMax, 1, fp);
	fread(sprite.sequences[1], sizeof(sequence_data_t) *sprite.seqMax, 1, fp);
	
	fclose(fp);

	return sprite;

}

int zse_sprites_sin_export(SPRITES_t *sprite ,char name[])
{

	char dirpos[74] = SPRITES_PARENTDIR;
	sprintf(dirpos, "%s%s%s", SPRITES_PARENTDIR, name, SPRITES_SINGLE_EXT);

	FILE *fp;
	fp = fopen(dirpos, "w+");
	if(fp == NULL)
	{
		return -1;
	}

	// Write Stuff
	// Version
	fwrite(ZSE_ENGINE_VERSION, sizeof(char) *8, 1, fp);
	// Attribute
/*
    uint16_t X;
    uint16_t Y;
    unsigned int frames;
    float dt;
    unsigned short colorused;
*/

	fwrite(&sprite[0], sizeof(SPRITES_t), 1, fp);

	fwrite(sprite->plot, sizeof(sprite_data_t) * sprite->X * sprite->Y * sprite->frames, 1, fp);

	fwrite(sprite->sequences[0], sizeof(sequence_data_t)*sprite->seqMax, 1, fp);
	fwrite(sprite->sequences[1], sizeof(sequence_data_t)*sprite->seqMax, 1, fp);


	fclose(fp);

	return 0;

}


void zse_delete_sprites_ptr(SPRITES_t *sprites, size_t siz)
{
	for (int i = 0; i < siz; ++i)
	{
		free(sprites[i].plot);
		free(sprites[i].sequences[0]);
		free(sprites[i].sequences[1]);
	}

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

	spr->sequences[0] = malloc(sizeof(sequence_data_t) * spr->seqMax);
	spr->sequences[1] = malloc(sizeof(sequence_data_t) * spr->seqMax);

	return spr;
}



/*
SPRITES_t *zse_sprites_migrate_BlocToSpr(SPRITES_BLOC_t spr_bloc, int *return_size)
{

}*/
