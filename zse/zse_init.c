#include "zse.h"
#include "zse_com.h"

int main(int argc, char const *argv[])
{

	if(zse_r_init())
	{
		return 1;
	}


	// Set the Main game Func
	zse_sprites_setup();

	zse_r_exit();

	return 0;
}