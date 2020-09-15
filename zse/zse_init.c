#include "zse.h"
#include "zse_com.h"

int main(int argc, char const *argv[])
{

	r_init();


	// Set the Main game Func
	zse_tile_maker_main ();

	r_exit();

	return 0;
}