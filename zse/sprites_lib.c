#include "sprites_lib.h"


SPRITES_t zse_sprites_sin_load(char name[])
{
	SPRITES_t sprite;

	char dirpos[74] = SPRITES_PARENTDIR;
	sprintf(dirpos, "%s%s%s", SPRITES_PARENTDIR, name, SPRITES_SINGLE_EXT);

	FILE *fp;
	if((fp = fopen(dirpos, "r")) == NULL)
	{
		printw("%s",dirpos);
		printw("UNABLE To LOAD Tile File\n");
		getch();
		return sprite;
	}

	char version[8];
	fread(version, sizeof(char) *8, 1, fp);
	fread(&sprite, sizeof(SPRITES_t) - sizeof(sdata*), 1, fp);

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

	fwrite(ZSE_ENGINE_VERSION, sizeof(char) *8, 1, fp);
	fwrite(&sprite[0], sizeof(SPRITES_t) - sizeof(sdata*), 1, fp);
	fwrite(sprite->plot, sizeof(sdata) * sprite->X * sprite->Y * sprite->frames, 1, fp);


	return 0;

}