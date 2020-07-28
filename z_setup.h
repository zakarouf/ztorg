#ifndef GAME_LIBRARY_H
#define GAME_LIBRARY_H


enum MENUSELECT{
	Ztg_DEBUGMODE,
	Ztg_PLAY_NORMAL,
	Ztg_EDITOR_NEW,
	Ztg_EDITOR_OPEN,
	Ztg_TEDITOR_NEW,
	Ztg_TEDITOR_OPEN,
};

int z_init_main(int mode);

#endif