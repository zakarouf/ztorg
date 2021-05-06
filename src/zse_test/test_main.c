#include <string.h>
#include <stdio.h>

#include "test.h"

#include "../zse/zse.h"
#include "../zse/map/map.h"
#include "../zse/map/map_ch_draw.h"
#include "../zse/io/tisk/tisk.h"
#define ZSE___TEST___SUCESSS true


static void _zse___TEST_map__draw(zset__MapCh *map)
{
	for (int i = 0; i < map->size.y; ++i)
	{
		for (int j = 0; j < map->size.x; ++j)
		{
			fputc(map->chunks[0][zse_xyz3Dto1D(j, i, 0, map->size.x, map->size.y)]+' ', stdout);
		}
		fputc('\n', stdout);
	}
}

static z__bool zse___TEST_map_export(void)
{
	zset__MapCh *map = zse_map__ch_createEmpty(10, 10, 1, 0);
	memset(map->chunks[0], 0, 10*10);

	zse_rtT__init();
//	zse_rtT_hideCursor();
	zse_rtT__D_set00();

	_zse___TEST_map__draw(map);
	map->chunks[0][2] = 2;
	map->chunks[0][88] = 2;
	map->chunks[0][44] = 2;

	z__Vint3 from = {{1, 1, 0}}
		   , to = {{4, 8, 0}};
	zse_map__draw_rec(map->chunks[0], (z__Vint2){{map->size.x, map->size.y}}, from, to, '.' - ' ');

	zse_rtT_getkey();
	zse_rtT__D_set00();
	_zse___TEST_map__draw(map);
	zse_rtT_getkey();

	zse_rtT__D_showCursor();
	zse_rtT__exit();

	zse_map__ch_export__st("foo", map);

	zse_map__ch_deleteChunks(map);

	return ZSE___TEST___SUCESSS;
}

static z__bool zse___TEST_map_load(void)
{
	zset__MapCh *map = zse_map__ch_load__st("foo");

	_zse___TEST_map__draw(map);

	zse_map__ch_deleteChunks(map);

	return ZSE___TEST___SUCESSS;
}

static void zse___TEST_printAsciiChart(void)
{
	for (z__u8 i = 32; i < 128; ++i)
	{
		printf("||%hhx||%03hhd||%c||\n", i, i, i);
	}
}

static z__bool zse___TEST_map(void)
{
	zse_rtT__init();
//	zse_rtT_hideCursor();
	zse_rtT__D_set00();



	zse___TEST_map_export();
	zse_rtT_getkey();


	printf("Loading...");
	zse_rtT_getkey();

	zse_rtT__D_set00();
	zse___TEST_map_load();
	zse_rtT_getkey();

	zse_rtT__D_showCursor();
	zse_rtT__exit();
	return ZSE___TEST___SUCESSS;
}

#include "../zse/sprite/sprite_char.h"
#include "../zse/io/tisk/tisk_sprite.h"
void zse___TEST_spriteChar_createNexport(void)
{
	zset__SpriteChar spr = zse_sprite__sChar_createEmpty(10, 10, 1, 0.5f, 4);

	memset(spr.plot, 'a', spr.x * spr.y * spr.frames);
	memset(spr.colormap, 5, spr.x * spr.y * spr.frames);

	zse_rtT__spriteChar__print(&spr, 0);
	puts("Saving... As Testspr.zspr");
	zse_sprite__sChar_export(&spr, "Testspr.zspr");
	zse_rtT_getkey();


	zse_sprite__sChar_delete(&spr);
}
void zse___TEST_spriteChar_load(void)
{
	puts("Loading Testspr.zspr");
	zset__SpriteChar spr = zse_sprite__sChar_load("Testspr.zspr");

	printf("Contents:"
		"x,y := %d,%d\n"
		"frames := %d\n"
		"dt := %f\n"
		"seqC := %d\n", spr.x, spr.y, spr.frames, spr.dt, spr.seq.count);

	zse_rtT__spriteChar__print(&spr, 0);
	zse_rtT_getkey();

}

void zse___TEST_spriteChar(void)
{
	zse___TEST_spriteChar_createNexport();
	zse___TEST_spriteChar_load();
}

#define ESC          27
#define INSERT       50
#define DELETE       51
#define PGUP         53
#define PGDN         54
#define ARROWRIGHT   67
#define ARROWLEFT    68
#define END          70
#define HOME         72
#define OTHER        79
#define BRACKETLEFT  91
#define TILDE       126
#define BACKSPACE   127

#include <sys/select.h>
#include <sys/ioctl.h>
#include <termios.h>
#include <unistd.h>


static const int STDIN = 0;
int kbhit(void)
{
    int bytesWaiting;

    ioctl(STDIN, FIONREAD, &bytesWaiting);
    return bytesWaiting;
}
void zse_rtT__D_setCurL(z__u32 times)
{
	fprintf(stdout, "\033[%dD", times);
}
void zse_rtT__D_setCurR(z__u32 times)
{
	fprintf(stdout, "\033[%dC", times);
}
void zse_rtT__D_eraseTillEndOfLine(void)
{
	printf("\033[K");
}

z__String zse_rtT__getString(z__char exitchar, z__u32 maxlen)
{
	z__String str = z__String_new(maxlen);

	z__i32 buffpos = 0;
	z__char tmpChar;
	while (str.used < maxlen && tmpChar != exitchar ) {
		tmpChar = zse_rtT_getkey();

		switch (1) {
		case ARROWLEFT: zse_rtT__D_setCurL(1); buffpos-- ;break;
		case ARROWRIGHT: zse_rtT__D_setCurR(1); buffpos++ ;break;
		case '\b': {
				z__String_delChar(&str, buffpos);
			}break;
		default: {
				z__String_insertChar(&str, tmpChar, buffpos);
				buffpos += 1;
			}break;
		};
		if (buffpos < 0) {
			buffpos = 0;
		}
		if (buffpos > str.used)
		{
			buffpos = str.used;
		}

		fputc('\r', stdout);fflush(stdout);
		zse_rtT__D_eraseTillEndOfLine();
		fputs(str.data, stdout);
		fflush(stdout);

	};

	return str;
}

void zse___TEST___tisk(void)
{
	z__String str = zse_rtT__getString('\n', 100);
	zse_rtT_io_printString(&str);
	printf(">>> ");
	zse_rtT_io_printString(&str);
}

int zse___TEST(void)
{
	//zse___TEST_map();
	//zse___TEST_spriteChar();
	//zse___TEST_printAsciiChart();
	//zse___TEST___curses();
	zse___TEST___tisk();
	return 0;
}
