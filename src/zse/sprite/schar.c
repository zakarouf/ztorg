#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "schar_def.h"
#include "../config/config_sprite_char.h"

void zse_sprite__sChar_export(const zse_T_Sprite_sChar *spr ,const char filename[ static 1 ])
{
	FILE *fp = fopen (filename, "wb");
	if (!fp)
	{
		return;
	}

	fwrite(ZSE_ENGINE_VERSION, ZSE_ENGINE_VERSION_SIGN_SIZE, 1, fp);

	fwrite(&spr->x, sizeof(spr->x), 1, fp);
	fwrite(&spr->y, sizeof(spr->y), 1, fp);
	fwrite(&spr->frames, sizeof(spr->frames), 1, fp);
	fwrite(&spr->dt, sizeof(spr->dt), 1, fp);
	fwrite(&spr->seq.count, sizeof(spr->seq.count), 1, fp);	

	fwrite(spr->plot, sizeof(*spr->plot), spr->x * spr->y * spr->frames, fp);
	fwrite(spr->colormap, sizeof(*spr->colormap), spr->x * spr->y * spr->frames, fp);

	fwrite(spr->seq.lens, sizeof(*spr->seq.lens), spr->seq.count, fp);

	for (int i = 0; i < spr->seq.count; ++i)
	{
		fwrite(spr->seq.data[i], sizeof(**spr->seq.data), spr->seq.lens[i], fp);
	}
	fclose(fp);
}

zse_T_Sprite_sChar zse_sprite__sChar_load(const char filename[ static 1 ])
{
	zse_T_Sprite_sChar spr = {0};

	FILE *fp = fopen (filename, "rb");
	if (!fp)
	{
		return spr;
	}

	char version[ZSE_ENGINE_VERSION_SIGN_SIZE];
	fread(version, ZSE_ENGINE_VERSION_SIGN_SIZE, 1, fp);

	fread(&spr.x, sizeof(spr.x), 1, fp);
	fread(&spr.y, sizeof(spr.y), 1, fp);
	fread(&spr.frames, sizeof(spr.frames), 1, fp);
	fread(&spr.dt, sizeof(spr.dt), 1, fp);
	fread(&spr.seq.count, sizeof(spr.seq.count), 1, fp);

	// Get Main Charset
	spr.plot = z__MALLOC(sizeof(*spr.plot) * spr.x * spr.y * spr.frames);
	fread(spr.plot, sizeof(*spr.plot), spr.x * spr.y * spr.frames, fp);

	// Get ForeGround Color
	spr.colormap = z__MALLOC(sizeof(*spr.colormap) * spr.x * spr.y * spr.frames);
	fread(spr.colormap, sizeof(*spr.colormap), spr.x * spr.y * spr.frames, fp);


	spr.seq.lens = z__MALLOC(sizeof(*spr.seq.lens) * spr.seq.count);
	fread(spr.seq.lens, sizeof(*spr.seq.lens), spr.seq.count, fp);

	spr.seq.data = z__MALLOC(sizeof(*spr.seq.data) * spr.seq.count);
	for (int i = 0; i < spr.seq.count; ++i)
	{
		spr.seq.data[i] = z__MALLOC(sizeof(**spr.seq.data) * spr.seq.lens[i]);
		fread(spr.seq.data[i], sizeof(**spr.seq.data), spr.seq.lens[i], fp);
	}

	fclose(fp);
	return spr;
}

void zse_sprite__sChar_delete(zse_T_Sprite_sChar *spr)
{
	z__FREE(spr->plot);
	z__FREE(spr->colormap);

	for (int i = 0; i < spr->seq.count; ++i)
	{
		z__FREE(spr->seq.data[i]);
	}
	z__FREE(spr->seq.data);
	z__FREE(spr->seq.lens);

	memset(spr, 0, sizeof(*spr));
}

zse_T_Sprite_sChar zse_sprite__sChar_createEmpty(z__u16 x, z__u16 y, z__u16 frames, z__float dt, z__u16 seqCount)
{
	zse_T_Sprite_sChar spr = {
		.x = x,
		.y = y,
		.frames = frames,
		.dt = dt,
		.plot = z__CALLOC(x * y * frames, sizeof(*spr.plot)),
		.colormap = z__CALLOC(x * y * frames, sizeof(*spr.colormap)),
		.seq.count = seqCount, 
		.seq.lens = (seqCount <= 0)? NULL : z__MALLOC(sizeof(*spr.seq.lens) * seqCount),
		.seq.data = (seqCount <= 0)? NULL : z__CALLOC(seqCount, sizeof(*spr.seq.data))
	};

	for (int i = 0; i < seqCount; ++i)
	{
		spr.seq.lens[i] = 3;
		spr.seq.data[i] = z__CALLOC(spr.seq.lens[i], sizeof(**spr.seq.data));
	}

	memset(spr.plot, ' ', spr.x * spr.y * spr.frames);

	return spr;
}

