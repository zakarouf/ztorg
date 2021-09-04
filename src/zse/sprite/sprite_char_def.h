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
	// union {
	// 	struct {
	// 		z__u8 _1, _2, _3, _4;
	// 	};
	// 	z__u32 raw;
	// } color;
	
	z__u16 *colormap;
    zset__spritechtype* plot;

    z__float dt;

    struct {
		z__size count;
		z__u16 *lens;
		z__u16 **data; } seq;

// for (int i = 0; i < seqSE[SeqNum]; ++i)
// {
//      seq[Seqnum][i];    
// }

}zse_T_Sprite_sChar;

#define ZSE_sprite__sChar_getX(spr) (spr).x
#define ZSE_sprite__sChar_getY(spr) (spr).y
#define ZSE_sprite__sChar_getFrames(spr) (spr).frames
#define ZSE_sprite__sChar_getTotalLen(spr) ((spr)->x * (spr)->y * (spr)->frames)

#define ZSE_sprite__sChar_getDt(spr) (spr).dt

#define ZSE_sprite__sChar_getMaxSeq(spr) (spr).seq.count
#define ZSE_sprite__sChar_getSeqLen(spr, of) (spr).seq.lens[of]
#define ZSE_sprite__sChar_getSeqData(spr, of) (spr).seq.data[of]

#define ZSE_sprite__sChar_setPlot(spr, _x, _y, _f, _plot) { (spr)->plot[zse_xyz3Dto1D((_x), (_y), (_f), (spr)->x, (spr)->y)] = _plot; }
#define ZSE_sprite__sChar_setColorFg(spr, _x, _y, _f, _color) { (spr)->colormap[zse_xyz3Dto1D((_x), (_y), (_f), (spr)->x, (spr)->y)] = _color; }
#define ZSE_sprite__sChar_setColorBg(spr, _x, _y, _f, _color) { (spr)->colormap[zse_xyz3Dto1D((_x), (_y), (_f), (spr)->x, (spr)->y)] = _color << 8; }

#define ZSE_sprite__sChar_getPlot(spr, _x, _y, _f) (spr).plot[zse_xyz3Dto1D((_x), (_y), (_f), spr.x, spr.y)]
#define ZSE_sprite__sChar_getColorFg(spr, _x, _y, _f) ((spr).colormap[zse_xyz3Dto1D((_x), (_y), (_f), spr.x, spr.y)]&0xff)
#define ZSE_sprite__sChar_getColorBg(spr, _x, _y, _f) ((spr).colormap[zse_xyz3Dto1D((_x), (_y), (_f), spr.x, spr.y)] >> 8)


#endif
