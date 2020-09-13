#include "zse/zse.h"

int main(int argc, char const *argv[])
{

	r_init();

	zse_tile_maker_main ();

	r_exit();

	return 0;
}