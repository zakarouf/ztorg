#include "sprites_lib.h"


SPRITES_t zse_sprites_sin_load(char name[])
{
	SPRITES_t sprite;

	char dirpos[74] = SPRITES_PARENTDIR;
	sprintf(dirpos, "%s%s%s", SPRITES_PARENTDIR, name, SPRITES_SINGLE_EXT);

	FILE *fp;
	if((fp = fopen(dirpos, "r")) == NULL)
	{
		printf("%s",dirpos);
		printf("UNABLE To LOAD Tile File\n");
		getch();
		return sprite;
	}

	// Read Stuff
	char version[8];
	fread(version, sizeof(char) *8, 1, fp);
	fread(&sprite, sizeof(SPRITES_t) - (sizeof(sdata*) - sizeof(COLORrgb_p*)), 1, fp);

	sprite.colorP = malloc(sizeof(COLORrgb_p) * sprite.colorused);
	fread(sprite.colorP, sizeof(COLORrgb_p)*sprite.colorused, 1, fp);

	sprite.plot = malloc(sizeof(sdata) * sprite.X * sprite.Y * sprite.frames);
	fread(sprite.plot, sizeof(sdata) * sprite.X * sprite.Y * sprite.frames, 1, fp);
	


	return sprite;

}

int zse_sprites_sin_export(SPRITES_t *sprite ,char name[])
{

	char dirpos[74] = SPRITES_PARENTDIR;
	sprintf(dirpos, "%s%s%s", SPRITES_PARENTDIR, name, SPRITES_SINGLE_EXT);

	FILE *fp;
	if((fp = fopen(dirpos, "w")) == NULL)
	{
		printw("%s",dirpos);
		printw("UNABLE To Creat Tile File\n");
		getch();
		return -1;
	}

	// Write Stuff
	fwrite("0.300000", sizeof(char) *8, 1, fp);
	fwrite(&sprite[0], sizeof(SPRITES_t) - sizeof(sdata*) - sizeof(COLORrgb_p*), 1, fp);

	fwrite(sprite->colorP, sizeof(COLORrgb_p)*sprite->colorused, 1, fp);
	fwrite(sprite->plot, sizeof(sdata) * sprite->X * sprite->Y * sprite->frames, 1, fp);


	return 0;

}


void zse_delete_sprites_ptr(SPRITES_t *sprites, size_t siz)
{
	for (int i = 0; i < siz; ++i)
	{
		free(sprites[i].plot);
		free(sprites[i].colorP);
	}

	free(sprites);
}

void zse_delete_sprites_blocCont(SPRITES_BLOC_t spr_bloc)
{
	for (int i = 0; i < spr_bloc.blocsize; ++i)
	{
		free(spr_bloc.sprites[i].plot);
	}
	free(spr_bloc.colorP);
	free(spr_bloc.sprites);
}

/*
SPRITES_t *zse_sprites_migrate_BlocToSpr(SPRITES_BLOC_t spr_bloc, int *return_size)
{

}*/