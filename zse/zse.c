/*-----------------------------------------------------
			Zakarouf's Sandbox Engine (ZSE)
//---------------------------------------------------//

	+-----------------------------------------------+
	| 			ZSE's Main 							|
	+-----------------------------------------------+
	

-----------------------------------------------------*/

#include "zse.h"
#include "../programs/tools_curses/zse_tools.h"


int demo_frogger();
int demo_2048 ();

//int demo_cave_hunter ();
int demo_perlin();
int zse_demo_screenSaver();
int ztorg(char name[]);
int ztorg_ray (char name[]);
int zse_tools_textEditor();

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

static int zse_main_arg_pha(int arc, char const *ar[])
{
	for (int i = 0; i < arc; ++i)
	{
		if (ar[i][0] == '-')
		{
			switch(ar[i][1])
			{
				case 'c':
					zse_rtC_colors_test_showall(stdscr, 0, 0);
					getch();
					return 0;
					break;
				case 't':
					if (ar[i][2] == 'm')
						zse_tool_mapEditor_st_main();
					else if (ar[i][2] == 's')
						zse_tool_spriteEditor_main();
					else if (ar[i][2] == 't')
						zse_tool_tileEditor_main ();
					else if (ar[i][2] == 'e')
						zse_tools_textEditor();
					return 0;
					break;
				case 'd':
					if (ar[i][2] == 'f')
						demo_frogger();
					else if (ar[i][2] == 'c')
						;//demo_cave_hunter();
					else if (ar[i][2] == '2')
						demo_2048();
					else if (ar[i][2] == 'p')
						demo_perlin();
					else if (ar[i][2] == 's')
						zse_demo_screenSaver();
					return 0;
					break;
				case 'z':
					ztorg((char *)ar[i+1]);
					return 0;
					break;
				case 'x':
					ztorg_ray((char*)ar[i+1]);
					return 0;
					break;
				case 'h':
					zse_rtC_exit();
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

int zse_initMainScreen_curses()
{
	if(zse_rtC_init())
	{
		return 1;
	}

	zse_rtC_color_initpairs();

	return 0;

}

#ifdef ZSE_CONFIG_SDL_ENABLE
int zse_initMainScreen_SDL()
{
	int zse_r_sdl_initscr(int x, int y);
	zse_r_sdl_initscr(600, 400);

	return 0;
}
#endif




int main(int argc, char const *argv[])
{

#ifdef ZSE_CONFIG_SDL_ENABLE
	zse_initMainScreen_SDL();
#endif
#ifdef ZSE_CONFIG_CURSES_ENABLE
	zse_initMainScreen_curses();
#endif

	//void zse_r_tiskTest();
	//zse_r_tiskTest();
	//void zse_render_vulkanInitTEST();	
	//	zse_render_vulkanInitTEST();

	srandom(clock());
	
	zse_main_arg_pha(argc, argv);
#ifdef ZSE_CONFIG_CURSES_ENABLE
	zse_rtC_exit();
#endif

	return 0;
}
