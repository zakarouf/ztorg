#include <stdlib.h>

#include "zse_tools.h"
#include "../../zse/io/curses/curses.h"


typedef struct _TEXT_FILE_RAW
{
	char *filedata;
	int size;
	int bytes_written;

	int *EOL_pos;
	int EOL_max;
	int EOL_count;

}FileData_t;

typedef struct _TEXT_FILE_CURSOR
{
	zse_int pos;
	zse_i8 key;

}ZSE_Cursor_t;

static FileData_t zse_tools_textEditor_CreateNewFile()
{	
	return (FileData_t) {
		.size = 1000,
		.bytes_written = 0,
		.filedata = malloc(sizeof(char)* 1000),

		.EOL_max = 100,
		.EOL_count = 1,
		.EOL_pos = calloc(100,  sizeof(int)),
		
 	};
}

static int zse_tools_textEditor_resize(FileData_t *f, int16_t by)
{
	f->size += by;
	f->filedata = realloc(f->filedata, f->size);
	if (f != NULL) {
		return 0;
	}
	else
		return 1;
}


static int zse_tools_textEditor_render(WINDOW *win, zse_Vint2 start, zse_Vint2 end, FileData_t *f, int At_line, ZSE_Cursor_t *c)
{
	int ch;

	if(At_line > f->EOL_count)
		return -1;
	else
		ch = f->EOL_pos[At_line];

	for (int j = start.y; j < end.y; j++)
	{
		for (int i = start.x; i < end.x; i++) 
		{
			if ( f->filedata[ch] != '\n' )
			{
				if(ch-1 == c->pos)
				{
					attron(COLOR_MAGENTA);
					mvwaddch(win, j, i, f->filedata[ch]);
					attrset(A_NORMAL);
				}
				else
					mvwaddch(win, j, i, f->filedata[ch]);
				
			}
			else
			{
				j++;i = start.x-1;
			}
			ch++;
			if (ch >= f->bytes_written)
				return 0;
		}
	}
	return 0;
}

static void zse_tools_textEditor_byteCheck(int *cu, int *byte)
{
	if (*cu == *byte)
	{
		byte[0]++;
	}	
}

static void zse_tools_textEditor_Savetextfile(FileData_t *f)
{
	char *fname = malloc(ZSE_MAX_FILENAME_SIZE * sizeof (char));
	char *final = malloc(ZSE_MAX_FILENAME_SIZE * sizeof (char));

	getnstr(fname, ZSE_MAX_FILENAME_SIZE);
	sprintf(final, "texts/%s", fname);

	FILE *fp = fopen(final, "w");

	fwrite(f->filedata, sizeof(char)*f->bytes_written, 1, fp);

	fclose(fp);

	free(fname);
	free(final);
}

int zse_tools_textEditor()
{

	FileData_t f = zse_tools_textEditor_CreateNewFile();
	ZSE_Cursor_t cursor = {0, 0};

	int render_AtLine = 0;

	while(TRUE)
	{
		cursor.key = getch();
		switch(cursor.key)
		{
			case 27:
				f.filedata[f.bytes_written] = '\0';
				zse_tools_textEditor_Savetextfile(&f);
				return 0;
				break;
			case 127:
				
				if (cursor.pos == f.bytes_written)
				{
					f.bytes_written--;
					if (f.bytes_written < 0)
						f.bytes_written = 0;
				}
				cursor.pos--;
				if (cursor.pos < 0)
					cursor.pos = 0;
				break;
			case 10:
				f.filedata[cursor.pos] = '\n';
				zse_tools_textEditor_byteCheck(&cursor.pos, &f.bytes_written);
				cursor.pos++;
				break;
			default:
				if (cursor.key >= 32 && cursor.key <= 126)
				{
					f.filedata[cursor.pos] = cursor.key;
					zse_tools_textEditor_byteCheck(&cursor.pos, &f.bytes_written);
					cursor.pos++;
					if (f.bytes_written > f.size )
						zse_tools_textEditor_resize(&f, 1000);
				}
				break;
		}

		clear();
		zse_tools_textEditor_render(stdscr, (zse_Vint2) {0, 0}, (zse_Vint2){getmaxx(stdscr), getmaxy(stdscr)}, &f, render_AtLine, &cursor);
		mvprintw(getmaxy(stdscr)-1, 0, "KEY :%hhd, POS: %d, SIZ: %d", cursor.key, cursor.pos, f.bytes_written);
		refresh();

	}

}
