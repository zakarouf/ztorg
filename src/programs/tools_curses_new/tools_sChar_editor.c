//#include <stdio.h> /* stirng & file */
#include <stdlib.h> /* memory */

#include "tools.h"
#include "../../zse/sys/sys.h"

#include "../../zse/io/curses/curses.h"
#include "../../zse/io/curses/curses_sprite.h"

#include "../../zse/sprite/sprite_char.h"
#include "../../zse/sprite/sprite_char_draw.h"

static const char *ZSE_T_SPRSR_OP_HELPTEXT[] = {
    "USAGE:",
    "w,a,s,d   Move Brush",
    "z, x      Move To Layer Up/Down",
    "c         Change Ink",
    "v         Toggle Brush",
    "b         Change Size",
    "l         Pick Color",
    
    "g,G,h,H   Change Foreground Colour",
    "r,R,t,T   Change Background Colour",
    
    
    ":         Commands",
    ":Cn       Copy Next Frame",
    ":Cp       Copy Previous Frame",
    ":Cs       Copy Selected Frame",
    
    ":Ss       Select Current Sprite Buffer",
    ":Sf       Select Current Sprite Frame",
    ":Sa       Select Current Sprite Buffer w/ Pos & Frame",
    ":Sp       Select Current Sprite Position",
    
    ":h        Help",
    ":w        Save",
    ":q        Quit",
};


struct zset_S_sprBrush
{
    z__Vint2 pos;
    z__i32 frame;

    struct {
        z__u32 size;
        z__u8 ink;
        z__u8 colorFg;
        z__u8 colorBg;
    } prop;

    struct {
        z__Vint2 pos;
        z__i32 frame;
        z__u8 color;
        z__u8 colorBg;
    } selection;

    zset__SpriteChar *sprCur;
    zset__SpriteChar *sprTmp;

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
            printw("Size Y :"); refresh(); scanw("%hd", &spr.y);
            printw("Frames :"); refresh(); scanw("%d", &spr.frames);
            printw("dt     :"); refresh(); scanw("%f", &spr.dt);
            printw("Seq    :"); refresh(); scanw("%d", &spr.seq.count);

            spr = zse_sprite__sChar_createEmpty(spr.x, spr.y, spr.frames, spr.frames, spr.seq.count);
            return spr;
        }
        else if (op == 'O')
        {
            z__StringLines filenames = z__file_getfnames("./sprites");
            zse_rtC__selectListS(stdscr, 0, 0, (const char **)filenames.data, filenames.lines, __tmpbuff, 32);
            z__StringLines_delete(&filenames);

            spr = zse_sprite__sChar_load(__tmpbuff);

            return spr;
        }
        else if (op == 'B')
        {
            return spr;
        }

    }
}

static void _tools_spr_sChar_editor_editSequence(zset__SpriteChar *spr)
{
    z__u16 frameCursor = 0;

    while (true)
    {

    }
}


void zse_tools_curses_spr_sChar_editor_mainloop(void)
{
    zse_rtC_init();
    WINDOW * status = newwin(5, getmaxx(stdscr), getmaxy(stdscr) - 5, 0);

    z__Arr(zset__SpriteChar) sprBuffer;
    z__Arr_new(&sprBuffer, 8);
    z__Arr_push(&sprBuffer, _tools_spr_sChar_editor_load_new());

    enum {_MAX_FOREGROUND_COLOR = 256, _MAX_BACKGROUND_COLOR = 16};
    struct zset_S_sprBrush Brush = {
        .pos.x = 0,
        .pos.y = 0,
        .frame = 0,
        .prop.ink = '@',
        .prop.colorFg = 0,
        .prop.colorBg = 0,
        .prop.size = 0,
        .sprCur = &z__Arr_getTop(sprBuffer),
        .sprTmp = &z__Arr_getTop(sprBuffer),
    };

    if (Brush.sprCur->x < 1 && Brush.sprCur->y < 1) {
        z__Arr_pop(&sprBuffer);
        goto _L__CLEANUP_and_EXIT;
    }

    char __Toggle[2][4] = {"Off", "On"};
    char __key = 0;
    zset_rtC_L_chtype cursor = '+';
    wclear(stdscr);
    noecho();

    while(true)
    {
        switch(__key) {
        case 'a':   Brush.pos.x -= 1; if (Brush.pos.x < 0) { Brush.pos.x += 1; }                         break;
        case 'd':   Brush.pos.x += 1; if (Brush.pos.x >= Brush.sprCur->x) { Brush.pos.x -= 1; }          break;
        case 'w':   Brush.pos.y -= 1; if (Brush.pos.y < 0) { Brush.pos.y += 1; }                        break;      
        case 's':   Brush.pos.y += 1; if (Brush.pos.y >= Brush.sprCur->y) { Brush.pos.y -= 1; }         break;

        case 'z':   Brush.frame -= 1; if (Brush.frame < 0) { Brush.frame += 1; }                        break;
        case 'x':   Brush.frame += 1; if (Brush.frame >= Brush.sprCur->frames) { Brush.frame -= 1; }    break;

        case 'c':   Brush.prop.ink = wgetch(status);                                                    break;
        case 'v':   Brush.toggle ^= 1;                                                                  break;

        case 'b':   echo();
                    Brush.prop.size = zse_rtC__mvmsgGetint(status, getmaxy(status)-1, 0, "Enter New Size >> ");
                    noecho();                                                                           break;

        case 'g':   Brush.prop.colorFg -= 1; if (Brush.prop.colorFg < 0) { Brush.prop.colorFg = _MAX_FOREGROUND_COLOR  -1; }  break;
        case 'h':   Brush.prop.colorFg += 1; if (Brush.prop.colorFg > _MAX_FOREGROUND_COLOR-1 ){ Brush.prop.colorFg = 0; }      break;
        case 'G':   Brush.prop.colorFg -= 6; if (Brush.prop.colorFg < 0) { Brush.prop.colorFg = _MAX_FOREGROUND_COLOR  -1; }   break;
        case 'H':   Brush.prop.colorFg += 6; if (Brush.prop.colorFg > _MAX_FOREGROUND_COLOR-1 ){ Brush.prop.colorFg = 0; }      break;

        case 'r':   Brush.prop.colorBg -= 1; if (Brush.prop.colorBg < 0) { Brush.prop.colorBg = _MAX_BACKGROUND_COLOR -1; }  break;
        case 't':   Brush.prop.colorBg += 1; if (Brush.prop.colorBg > _MAX_BACKGROUND_COLOR){ Brush.prop.colorBg = 0; }      break;
        case 'R':   Brush.prop.colorBg -= 6; if (Brush.prop.colorBg < 0) { Brush.prop.colorBg = _MAX_BACKGROUND_COLOR -1; }   break;
        case 'T':   Brush.prop.colorBg += 6; if (Brush.prop.colorBg > _MAX_BACKGROUND_COLOR){ Brush.prop.colorBg = 0; }      break;

        // Options
        case ':':
            do {
                echo();
                z__char tmpop = mvwgetch(status, getmaxy(status) -1, 0);

                if (tmpop == 'w') {   
                    mvwaddstr(status, getmaxy(status) -1, 0, "Enter Name: ");
                    char *name = z__MALLOC(sizeof(char) * 32);
                    wgetnstr(status, name, 32);
                    zse_sprite__sChar_export(Brush.sprCur, name);
                    z__FREE(name);

                    zse_rtC_clearLine_set0(status);
                    mvwaddstr(status, getmaxy(status) -1, 0, "Sprite Saved");
                    zse_rtC_clearLine_set0(status);

                } else if (tmpop == 'C') {
                    mvwaddstr(status, getmaxy(status) -1, 0, "Copy |n|p|s| ");
                    tmpop = mvwgetch(status, getmaxy(status) -1, 0);
                    
                    if (tmpop == 'n') {
                        if (Brush.frame+1 < Brush.sprCur->frames ) {
                    	    zse_sprite__sChar_copyFrame(Brush.sprCur, Brush.frame+1, Brush.frame);
                    	}
                    } else if ( tmpop == 'p') {
                        if (Brush.frame-1 >= 0) {
                       	    zse_sprite__sChar_copyFrame(Brush.sprCur, Brush.frame-1, Brush.frame);
                        }
                    } else if (tmpop == 's') {
                        zse_sprite__sChar_copyFrame(Brush.sprCur, Brush.selection.frame, Brush.frame);
                    }

                    zse_rtC_clearLine_set0(status);

                } else if (tmpop == 'S') {
                    mvwaddstr(status, getmaxy(status) -1, 0, "Select |f|a|p|s| ");
                    
                    switch(mvwgetch(status, getmaxy(status) -1, 0)) {
                    case 'f':   Brush.selection.frame = Brush.frame; break;
                    case 'p':   Brush.selection.pos = Brush.pos;     break;
                    case 's':   Brush.sprTmp = Brush.sprCur;         break;
                    case 'a':   {
                                    Brush.sprTmp = Brush.sprCur;
                                    Brush.selection.pos = Brush.pos;
                                    Brush.selection.frame = Brush.frame;
                                }                                    break;
                        }

                    zse_rtC_clearLine_set0(status);
                } else if (tmpop == 'R') {
                    // TODO: Record a sequence
                } else if (tmpop == 'h') {
                    zse_rtC__selectListS(stdscr, 0,  0, ZSE_T_SPRSR_OP_HELPTEXT, 20, &tmpop, 0);
                } else if (tmpop == 'q') {
                    goto _L__CLEANUP_and_EXIT;
                }

                noecho();
            } while(0);
            break;
        default:
            break;
        }

        int _color_tmp = (Brush.prop.colorBg << 8) | Brush.prop.colorFg;
        if(Brush.toggle)
        {
            zse_sprite__sCharDraw_circle( Brush.sprCur
                , (z__Vint3){Brush.pos.x, Brush.pos.y ,Brush.frame}
                , Brush.prop.size, Brush.prop.ink, _color_tmp);
        }


        werase(stdscr);

        zse_rtC__sprite__sChar_PrintPadEnd(stdscr, 0, 0, 0, getmaxy(status), Brush.sprCur, Brush.frame);
        
        mvwprintw(status, 0, 0,"Brush[%3s] -> %c {%s} :: %d =Color={%hi|%hi} "
            , __Toggle[Brush.toggle], Brush.prop.ink , "NONE", Brush.prop.size, Brush.prop.colorFg, Brush.prop.colorBg);

        wcolor_set(status, _color_tmp , NULL);
        waddstr(status,"##  \n");
        wattr_set(status, A_NORMAL, 0, NULL);

        mvwaddch(stdscr, Brush.pos.y, Brush.pos.x, cursor | COLOR_PAIR(_color_tmp));

        mvwprintw(status, 1, 0, "POS [%hd,%hd] Frame - %3d/%3d Color No. %d"
            , Brush.pos.x, Brush.pos.y, Brush.frame, Brush.sprCur->frames-1, ZSE_sprite__sChar_getColorFg(Brush.sprCur[0], Brush.pos.x, Brush.pos.y, Brush.frame));

        //mvwprintw(status, 2, 0, "Show: Colors %d  TransEnable %d  TransShow %d",
        //    r_options&ZSE_T_SPRSR_OP_COLORS? 1:0, r_options&ZSE_T_SPRSR_OP_TRANSENAB? 1:0, r_options&ZSE_T_SPRSR_OP_TRANSSHOW? 1:0);
        
        wrefresh(stdscr);
        //wrefresh(status);

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
