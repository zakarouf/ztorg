#ifndef ZAKAROUF_ZSE__SPRITE_CHAR_DEFINATION_H
#define ZAKAROUF_ZSE__SPRITE_CHAR_DEFINATION_H

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

typedef z__u8 zset__spritechtype;

typedef struct _ZSE_SPRITE_TYPE_Char_STRUCT
{
    z__u16 x, y, frames;
    z__u8* colormap;
    zset__spritechtype* plot;

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

#define ZSE_sprite__Char_getX(spr) spr.x
#define ZSE_sprite__Char_getY(spr) spr.y
#define ZSE_sprite__Char_getFrames(spr) spr.frames
#define ZSE_sprite__Char_getTotalLen(spr) ((spr)->x * (spr)->y * (spr)->frames)

#define ZSE_sprite__Char_getDt(spr) spr.dt

#define ZSE_sprite__Char_getMaxSeq(spr) spr.seq.count
#define ZSE_sprite__Char_getSeqLen(spr, of) spr.seq.lens[of]
#define ZSE_sprite__Char_getSeqData(spr, of) spr.seq.data[of]

#define ZSE_sprite__Char_setPlot(spr, _x, _y, _f, plot) { (spr)->plot[zse_xyz3Dto1D((_x), (_y), (_f), (spr)->x, (spr)->y)] = plot; }
#define ZSE_sprite__Char_setColor(spr, _x, _y, _f, color) { (spr)->colormap[zse_xyz3Dto1D((_x), (_y), (_f), (spr)->x, (spr)->y)] = color; }

#define ZSE_sprite__Char_getPlot(spr, _x, _y, _f) spr.plot[zse_xyz3Dto1D((_x), (_y), (_f), spr.x, spr.y)]
#define ZSE_sprite__Char_getColor(spr, _x, _y, _f) spr.colormap[zse_xyz3Dto1D((_x), (_y), (_f), spr.x, spr.y)]


#endif