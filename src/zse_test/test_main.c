#include <string.h>
#include <stdio.h>

#include "../zse/zse.h"
#include "../zse/map_new/map.h"
#include "../zse/io/tisk/tisk.h"
#define ZSE___TEST___SUCESSS true


static void _zse___TEST_map__draw(zset__mapCh *map)
{
	for (int i = 0; i < map->size.y; ++i)
	{
		for (int j = 0; j < map->size.x; ++j)
		{
			fputc(map->chunks[0][zse_xyz3Dto1D(j, i, 0, map->size.x, map->size.y)]+67, stdout);
		}
		fputc('\n', stdout);
	}
}

static z__bool zse___TEST_map_export(void)
{
	zset__mapCh *map = zse_map__ch_createEmpty(10, 10, 1, 1);
	memset(map->chunks[0], 0, 10*10);

	zse_rtT_init();
//	zse_rtT_hideCursor();
	zse_rtT__set00();

	_zse___TEST_map__draw(map);
	map->chunks[0][2] = 2;
	map->chunks[0][88] = 2;
	map->chunks[0][44] = 2;
	zse_rtT_getkey();
	zse_rtT__set00();
	_zse___TEST_map__draw(map);
	zse_rtT_getkey();

	zse_rtT_showCursor();
	zse_rtT_exit();

	zse_map__ch_export__st("foo", map);

	zse_map__ch_deleteChunks(map);

	return ZSE___TEST___SUCESSS;
}

static z__bool zse___TEST_map_load(void)
{
	zset__mapCh *map = zse_map__ch_load__st("foo");

	_zse___TEST_map__draw(map);

	zse_map__ch_deleteChunks(map);

	return ZSE___TEST___SUCESSS;
}

static z__bool zse___TEST_map(void)
{
	zse_rtT_init();
//	zse_rtT_hideCursor();
	zse_rtT__set00();



	zse___TEST_map_export();
	zse_rtT_getkey();


	printf("Loading...");
	zse_rtT_getkey();

	zse___TEST_map_load();
	zse_rtT_getkey();




	zse_rtT_getkey();
	zse_rtT_showCursor();
	zse_rtT_exit();
	return ZSE___TEST___SUCESSS;
}

int zse___TEST(void)
{
	zse___TEST_map();
	return 0;
}