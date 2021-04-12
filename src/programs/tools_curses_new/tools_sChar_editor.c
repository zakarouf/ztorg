//#include <stdio.h> /* stirng & file */
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


struct zset_S_sprBrush
{
    z__Vint2 pos;
    z__i32 frame;

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
        clear();
        printw("(N)ew | (O)pen | Go(B)ack : ");
        z__u8 op = getch();

        if (op == 'N')
        {
            printw("\nSize X :"); refresh(); scanw("%hd", &spr.x);
            printw("\nSize Y :"); refresh(); scanw("%hd", &spr.y);
            printw("\nFrames :"); refresh(); scanw("%d", &spr.frames);
            printw("\ndt     :"); refresh(); scanw("%f", &spr.dt);
            printw("\nSeq    :"); refresh(); scanw("%d", &spr.seq.count);

            spr = zse_sprite__sChar_createEmpty(spr.x, spr.y, spr.frames, spr.frames, spr.seq.count);
            return spr;
        }
        else if (op == 'O')
        {
            printw("\nName   :"); scanw("%s", __tmpbuff);
            spr = zse_sprite__sChar_load(__tmpbuff);

            return spr;
        }
        else if (op == 'B')
        {
            return spr;
        }

    }
}

void zse_tools_curses_spr_sChar_editor_mainloop(void)
{
    zse_rtC_init();
    WINDOW * status = newwin(5, getmaxx(stdscr), getmaxy(stdscr) - 5, 0);

    z__Arr(zset__SpriteChar) sprBuffer;
    z__Arr_create(&sprBuffer, 8);

    z__Arr_push(&sprBuffer, _tools_spr_sChar_editor_load_new());
    zset__SpriteChar *spr_current_buffer = &z__Arr_getTop(sprBuffer);
                     //*spr_tmp_buffer = NULL;

    if (spr_current_buffer->x < 1 && spr_current_buffer->y < 1) {
        z__Arr_pop(&sprBuffer);
        goto _L__CLEANUP_and_EXIT;
    }

    struct zset_S_sprBrush Brush = {
        .pos.x = 0,
        .pos.y = 0,
        .frame = 0,
        .prop.ink = '@',
        .prop.color = 0,
        .prop.size = 0,
    };


    char __Toggle[2][4] = {"Off", "On"};
    char __key = 0;
    zset_rtC_L_chtype cursor = '+';
    wclear(stdscr);
    noecho();

    while(true)
    {
        switch(__key) {
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
            case 'z':
                Brush.frame -= 1;
                if (Brush.frame < 0) {
                    Brush.frame += 1;
                }
                break;
            case 'x':
                Brush.frame += 1;
                if (Brush.frame >= spr_current_buffer->frames) {
                    Brush.frame -= 1;
                }
                break;


            case 'c':
                Brush.prop.ink = wgetch(status);
                break;

            case 'v':
                Brush.toggle ^= 1;
                break;

            case 'b':
                echo();
                Brush.prop.size = zse_rtC__mvmsgGetint(status, getmaxy(status)-1, 0, "Enter New Size >> ");
                noecho();
                break;

            case 'g':
                Brush.prop.color -= 1;
                if(Brush.prop.color < 0){Brush.prop.color = COLORS -1;}
                break;
            case 'h':
                Brush.prop.color += 1;
                if(Brush.prop.color > COLORS){Brush.prop.color = 0;}
                break;
            case 'G':
                Brush.prop.color -= 6;
                if(Brush.prop.color < 0){Brush.prop.color = COLORS -1;}
                break;
            case 'H':
                Brush.prop.color += 6;
                if(Brush.prop.color > COLORS){Brush.prop.color = 0;}
                break;

            // Options
            case ':':
                do {
                    echo();
                    z__char tmpop = mvwgetch(status, getmaxy(status) -1, 0);

                    if (tmpop == 'w') {   
                        mvwprintw(status, getmaxy(status) -1, 0, "Enter Name: ");
                        char *name = z__MALLOC(sizeof(char) * 32);
                        wgetnstr(status, name, 32);
                        zse_sprite__sChar_export(spr_current_buffer, name);

                    } else if (tmpop == 'q') {
                        goto _L__CLEANUP_and_EXIT;
                    }

                    noecho();
                } while(0);
                break;
            default:
                break;
        }

        if(Brush.toggle)
        {
            zse_sprite__sCharDraw_circle( spr_current_buffer
                , (z__Vint3){Brush.pos.x, Brush.pos.y ,Brush.frame}
                , Brush.prop.size, Brush.prop.ink, Brush.prop.color);
        }

        zse_rtC__sprite__sChar_PrintPadEnd(stdscr, 0, 0, 0, getmaxy(status), spr_current_buffer, Brush.frame);
        mvwaddch(stdscr, Brush.pos.y, Brush.pos.x, cursor | COLOR_PAIR(Brush.prop.color));
        


        mvwprintw(status, 0, 0,"Brush[%3s] -> %c {%s} :: %d =Color={%hi}"
            , __Toggle[Brush.toggle], Brush.prop.ink , "NONE", Brush.prop.size, Brush.prop.color);

        wattrset(status, COLOR_PAIR(Brush.prop.color));
        waddstr(status,"##  \n");


        wattrset(status, A_NORMAL);


        mvwprintw(status, 1, 0, "POS [%hd,%hd] Frame - %3d/%3d Color No. %d"
            , Brush.pos.x, Brush.pos.y, Brush.frame, spr_current_buffer->frames-1, ZSE_sprite__sChar_getColor(spr_current_buffer[0], Brush.pos.x, Brush.pos.y, Brush.frame));

        //mvwprintw(status, 2, 0, "Show: Colors %d  TransEnable %d  TransShow %d",
        //    r_options&ZSE_T_SPRSR_OP_COLORS? 1:0, r_options&ZSE_T_SPRSR_OP_TRANSENAB? 1:0, r_options&ZSE_T_SPRSR_OP_TRANSSHOW? 1:0);

        wrefresh(status);
        wrefresh(stdscr);

        __key = wgetch(status);
    }

    _L__CLEANUP_and_EXIT: {
        for (int i = 0; i < z__Arr_getUsed(sprBuffer); ++i)
        {
            zse_sprite__sChar_delete(&sprBuffer.data[i]);
        }
        z__Arr_delete(&sprBuffer);

        delwin(status);
        echo();
        zse_rtC_exit();
        return;
    }
}
