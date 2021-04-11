#include <stdio.h> /* stirng & file */
#include <stdlib.h> /* memory */

#include "tools.h"

#include "../../zse/io/curses/curses.h"
#include "../../zse/io/curses/curses_sprite.h"

#include "../../zse/sprite/sprite_char.h"
#include "../../zse/sprite/sprite_char_draw.h"

#define ZSE_T_SPRSR_OP_HELPTEXT \
    "Sprite Help:\n"\
    "w,a,s,d   Move Brush\n"\
    "z, x      Move To Layer Up/Down\n"\
    "c         Change Ink\n"\
    "v         Toggle Brush\n"\
    "b         Change Size\n"\
    "p         Pick Brush\n"\
    "l         Pick Color\n"\
    "h         Realloc Frames\n"\
    "r         Change dt\n"\
    ":         Commands\n"\
    "e         Apply Colour\n"\
    "-,=,_,+   Change Colour\n"\
    "`         Exit\n"
