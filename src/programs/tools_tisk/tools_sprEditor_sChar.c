
#include <stdlib.h>
#include <stdio.h>
#include "../../zse/io/tisk/tisk.h"
#include "../../zse/io/tisk/tisk_sprite.h"

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


struct zset_S_sprBrush
{
	z__Vint2 pos;
	z__u32 frame;

	struct {
		z__u32 size;
		z__u8 ink;
		z__u8 color;
	} prop;

	z__bool toggle;
};

static zset__SpriteChar _tools_spr_sChar_editor_load_new(void)
{
    zset__SpriteChar spr = {0};
    z__char __tmpbuff[32];

    
    while(true) {
        zse_rtT__set00();
        fputs("(N)ew | (O)pen | Go(B)ack", stdout);
        z__u8 op = zse_rtT_getkey();

        if (op == 'N')
        {
            zse_rtT__io_input(__tmpbuff, "\nSize X :" ,sizeof(__tmpbuff)); spr.x = atoi(__tmpbuff);
            zse_rtT__io_input(__tmpbuff, "\nSize Y :" ,sizeof(__tmpbuff)); spr.y = atoi(__tmpbuff);
            zse_rtT__io_input(__tmpbuff, "\nFrames :" ,sizeof(__tmpbuff)); spr.frames = atoi(__tmpbuff);
            zse_rtT__io_input(__tmpbuff, "\ndt     :" ,sizeof(__tmpbuff)); spr.dt = atof(__tmpbuff);
            zse_rtT__io_input(__tmpbuff, "\nSeq    :" ,sizeof(__tmpbuff)); spr.seq.count = atoi(__tmpbuff);

            spr = zse_sprite__sChar_createEmpty(spr.x, spr.y, spr.frames, spr.frames, spr.seq.count);
            return spr;
        }
        else if (op == 'O')
        {
            zse_rtT__io_input(__tmpbuff, "\nName   :" ,sizeof(__tmpbuff));
            spr = zse_sprite__sChar_load(__tmpbuff);

            return spr;
        }
        else if (op == 'B')
        {
            return spr;
        }

    }
}

void zse_tools__spr_sChar_editor_mainloop(void)
{
    zse_rtT_init();

    z__Arr(zset__SpriteChar) sprBuffer;
    z__Arr_create(&sprBuffer, 8);

    z__Arr_push(&sprBuffer, _tools_spr_sChar_editor_load_new());
    zset__SpriteChar *spr_current_buffer = &z__Arr_getTop(sprBuffer);

    if (spr_current_buffer->x < 1 && spr_current_buffer->y < 1) {
        z__Arr_pop(&sprBuffer);
        goto _L__CLEANUP_and_EXIT;
    }

    struct zset_S_sprBrush Brush = {0};

    while(true)
    {
        switch(zse_rtT_getkey()) {
            case 'a':
                Brush.pos.x-= 1;
                if (Brush.pos.x < 0) {
                    Brush.pos.x += 1;
                }
                break;

            case 'd':
                Brush.pos.x+= 1;
                if (Brush.pos.x >= spr_current_buffer->x) {
                    Brush.pos.x -= 1;
                }
                break;
            
            case 'w':
                Brush.pos.y -= 1;
                if (Brush.pos.y < 0) {
                    Brush.pos.y += 1;
                }
                break;
            
            case 's':
                Brush.pos.y += 1;
                if (Brush.pos.y >= spr_current_buffer->y) {
                    Brush.pos.y -= 1;
                }
                break;
            
            case 'c':
                scanf("%c", &Brush.prop.ink);
                break;

            case 't':
                Brush.toggle ^= 1;
                break;

            case 127:
                goto _L__CLEANUP_and_EXIT;
                break;
                
            default:
                break;
        }
        ZSE_sprite__sChar_setPlot(spr_current_buffer, Brush.pos.x, Brush.pos.y, Brush.frame , Brush.prop.ink );

        zse_rtT__spriteChar__print(spr_current_buffer, Brush.frame);
        zse_rtT__setCur(Brush.pos.x, Brush.pos.y);
        fputc('@', stdout);
        zse_rtT__setCur(0, spr_current_buffer->y + 1);


    }

    _L__CLEANUP_and_EXIT: {
        for (int i = 0; i < z__Arr_getUsed(sprBuffer); ++i)
        {
            zse_sprite__sChar_delete(&sprBuffer.data[i]);
        }
        z__Arr_delete(&sprBuffer);

        zse_rtT_exit();
        return;
    }
}
