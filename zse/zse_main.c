/*-----------------------------------------------------
			Zakarouf's Sandbox Engine (ZSE)
//---------------------------------------------------//

	+-----------------------------------------------+
	| 			ZSE's Main 							|
	+-----------------------------------------------+
	

-----------------------------------------------------*/

#include "zse.h"
#include "tools_curses/zse_tools.h"

int zse_colors_test_showall();
int frogger();


int zse_main_arg_pha(int arc, char const *ar[])
{
	for (int i = 0; i < arc; ++i)
	{
		if (ar[i][0] == 'r')
		{
			zse_colors_test_showall();
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

	zse_r_color_initpairs(COLORS);
	zse_main_arg_pha(argc, argv);
	
	// Set the Main game Func [select only one]
	 zse_tool_spriteEditor_main();
	//frogger();


	zse_r_exit();

	return 0;
}