#ifndef ZAKAROUF_ZSE__SPRITE_CHAR_H
#define ZAKAROUF_ZSE__SPRITE_CHAR_H

#include "../common.h"


/* Sprite Char Type 
 * ------------------
 * 1. x, y : Determines the length and width of the sprite.
 * 2. frames : How many Frames layers it have
 * 3. Therefore, Total data size is x * y * frames * sizeof plot
 * 4. dt : Animation Speed for frame, e.g. 1/30 == 30fps.
 * 5. seq : Sequenses, for storing snippits of animations.
 */

/* Plot data
 *-----------
 * FFFF FFFF  <== PlotPoint
 *  ^    ^ 
 *  |    |= Character
 *  |= Color Code (8bit ANSI)
 *-----------
 * Compactible with ncurses
 */

typedef struct _ZSE_SPRITE_TYPE_Char_STRUCT
{
    z__u16 x, y, frames;
    z__u8* colormap;
    z__u8* plot;

    z__float dt;

    struct { 
    	z__i16 count;
    	z__i16* lens;
    	z__u16** data; } seq ;
    

// for (int i = 0; i < seqSE[SeqNum]; ++i)
// {
//      seq[Seqnum][i];    
// }

}zset__SpriteChar;

#define ZSE_sprite__Char_setColor(spr, x, y, f, color) \
	{ 																			\
		(spr)->colormap[zse_xyz3Dto1D(x, y, f, (spr)->x, (spr)->y)] = color; 	\
	}


#endif