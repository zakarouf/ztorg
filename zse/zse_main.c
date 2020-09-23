#include "zse.h"
#include "tools_curses/zse_tools.h"

int main(int argc, char const *argv[])
{

	if(zse_r_init())
	{
		return 1;
	}


	// Set the Main game Func
	zse_tool_spriteEditor_main();

	zse_r_exit();

	return 0;
}