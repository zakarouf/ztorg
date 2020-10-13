/*-----------------------------------------------------
			Zakarouf's Sandbox Engine (ZSE)
//---------------------------------------------------//

	+-----------------------------------------------+
	| 			ZSE's Main 							|
	+-----------------------------------------------+
	

-----------------------------------------------------*/

#include "zse.h"
#include "tools_curses/zse_tools.h"


int demo_frogger();
int demo_2048 ();
int demo_cave_hunter ();

#define ZSE_ARG_COMMANDS_HELP \
	"Ztorg (c) Zakarouf 2020\n"\
	"\n\n"\
	"-c\t Show Colors\n"\
	"-t\t Tools\n"\
	"\t\tm\t Map Editor\n"\
	"\t\ts\t Sprite Editor\n"\
	"\t\tt\t Tile Editor\n\n"\
	"-d\t Demos\n"\
	"\t\tf\t Frogger\n"\
	"\t\tc\t Cave Hunter\n"\
	"\t\t2\t 2048\n"\

int zse_main_arg_pha(int arc, char const *ar[])
{
	for (int i = 0; i < arc; ++i)
	{
		if (ar[i][0] == '-')
		{
			switch(ar[i][1])
			{
				case 'c':
					zse_colors_test_showall(stdscr, 0, 0);
					getch();
					break;
				case 't':
					if (ar[i][2] == 'm')
						zse_tool_mapEditor_st_main();
					else if (ar[i][2] == 's')
						zse_tool_spriteEditor_main();
					else if (ar[i][2] == 't')
						zse_tool_tileEditor_main ();
					break;
				case 'd':
					if (ar[i][2] == 'f')
						demo_frogger();
					else if (ar[i][2] == 'c')
						demo_cave_hunter();
					else if (ar[i][2] == '2')
						demo_2048();
					break;
				case 'h':
					zse_r_exit();
					fprintf(stdout ,ZSE_ARG_COMMANDS_HELP);
					return 0;
					break;
				default:
					break;
			}


		}
	}

	return 0;
}

int main(int argc, char const *argv[])
{

	if(zse_r_init())
	{
		return 1;
	}
	srandom(clock());

	zse_r_color_initpairs();
	zse_main_arg_pha(argc, argv);
	

	zse_r_exit();

	return 0;
}