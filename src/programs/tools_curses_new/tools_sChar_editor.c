//#include <stdio.h> /* stirng & file */
#include <stdlib.h> /* memory */

#include "tools.h"
#include "../../zse/sys/sys.h"

#include "../../zse/io/curses/curses.h"
#include "../../zse/io/curses/curses_sprite.h"

#include "../../zse/sprite/sprite_char.h"
#include "../../zse/sprite/sprite_char_draw.h"

static const char ZSE_T_SPRSR_OP_HELPTEXT_ITEMS = 21;
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
    
    ":N        New tab",
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

    zse_T_Sprite_sChar *sprCur;
    zse_T_Sprite_sChar *sprTmp;

    z__bool toggle;
};


static zse_T_Sprite_sChar _tools_spr_sChar_editor_load_new(void)
{
    zse_T_Sprite_sChar spr = {0};
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
            z__StringList filenames = z__io_getfnames("./sprites");
            zse_rtC__selectListS(stdscr, 0, 0, (const char **)filenames.str_list, filenames.ll_used, __tmpbuff, 32);
            z__StringList_delete(&filenames);

            spr = zse_sprite__sChar_load(__tmpbuff);

            return spr;
        }
        else if (op == 'B')
        {
            return spr;
        }

    }
}

static void _tools_spr_sChar_editor_editSequence(zse_T_Sprite_sChar *spr)
{
    z__u16 frameCursor = 0;

    while (true)
    {
        switch(getch())
        {
            case 'a': frameCursor--;
            case 'd': frameCursor++;
            case 'q':return;
        }
    }
}

void _reset_brush_except_cur_n_tmp(struct zset_S_sprBrush *brsh)
{
    brsh->pos.x = 0;
    brsh->pos.y = 0;
    brsh->frame = 0;
    brsh->prop.ink = 'a';
    brsh->prop.colorFg = 0;
    brsh->prop.colorBg = 0;
    brsh->prop.size = 0;
}

void zse_tools_curses_spr_sChar_editor_mainloop(void)
{
    zse_rtC_init();
    WINDOW * status = newwin(5, getmaxx(stdscr), getmaxy(stdscr) - 5, 0);

    /* Using Linked list to emulate tabs */
    z__Link(sprBuffer_ll, zse_T_Sprite_sChar);
    z__LList(sprBuffer_ll, int current) sprBuffer;
    z__LList_new(&sprBuffer, _tools_spr_sChar_editor_load_new());
    sprBuffer.current = 0;

    enum {_MAX_FOREGROUND_COLOR = 256, _MAX_BACKGROUND_COLOR = 128};
    struct zset_S_sprBrush Brush = {
        .sprCur = &sprBuffer.cursor->data,
        .sprTmp = &sprBuffer.cursor->data,
    };
    _reset_brush_except_cur_n_tmp(&Brush);

    if (Brush.sprCur->x < 1 && Brush.sprCur->y < 1) {
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

        case ']':   if (sprBuffer.cursor->next) {
                        sprBuffer.cursor = sprBuffer.cursor->next;
                        Brush.sprCur = &sprBuffer.cursor->data;
                        sprBuffer.current++;
                    } else {
                        sprBuffer.cursor = sprBuffer.tail; Brush.sprCur = &sprBuffer.cursor->data;
                        sprBuffer.current = 0;
                    }
                    _reset_brush_except_cur_n_tmp(&Brush);
                    break;

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
                } else if (tmpop == 'N') {
                    z__LList_pushHead(&sprBuffer, _tools_spr_sChar_editor_load_new());
                    if (sprBuffer.head->data.x < 1 && sprBuffer.head->data.y < 1) {
                        z__LList_popHead(&sprBuffer);
                    } else {
                        Brush.sprCur = &sprBuffer.head->data;
                        z__LList_setCursorHead(&sprBuffer);
                    }
                } else if (tmpop == 'R') {
                    _tools_spr_sChar_editor_editSequence(Brush.sprCur);
                } else if (tmpop == 'h') {
                    zse_rtC__selectListS(stdscr, 0,  0, ZSE_T_SPRSR_OP_HELPTEXT, ZSE_T_SPRSR_OP_HELPTEXT_ITEMS, &tmpop, 0);
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
                , (z__Vint3){{Brush.pos.x, Brush.pos.y ,Brush.frame}}
                , Brush.prop.size, Brush.prop.ink, _color_tmp);
        }


        werase(stdscr);

        zse_rtC__sprite__sChar_PrintPadEnd(stdscr, 0, 0, 0, getmaxy(status), Brush.sprCur, Brush.frame);
        
        mvwprintw(status, 0, 0,"Brush[%3s] -> %c {%s} :: %d =Color={%hi|%hi} "
            , __Toggle[Brush.toggle], Brush.prop.ink , "NONE", Brush.prop.size, Brush.prop.colorFg, Brush.prop.colorBg);

        wcolor_set(status, _color_tmp , NULL);
        waddstr(status,"##  \n");
        wattr_set(status, A_NORMAL, 0, NULL);

        // Draw Brush
        mvwaddch(stdscr, Brush.pos.y, Brush.pos.x, cursor | COLOR_PAIR(_color_tmp));

        
        mvwprintw(status, 1, 0, "POS [%hd,%hd] Frame - %3d/%3d Color No. %d"
            , Brush.pos.x, Brush.pos.y, Brush.frame, Brush.sprCur->frames-1, ZSE_sprite__sChar_getColorFg(Brush.sprCur[0], Brush.pos.x, Brush.pos.y, Brush.frame));

        mvwprintw(status, 3, 0, "Current: %d"
            , sprBuffer.current);


        /* Draw Tabs */
        z__LinkDef(sprBuffer_ll) *tmpTab_cursor = sprBuffer.tail;
        int i = 0;
        for(; i < getmaxy(stdscr)-2 && tmpTab_cursor; ++i)
        {
            if (i == sprBuffer.current)
            {
                wcolor_set(stdscr, 1, NULL);
            }
            mvwprintw(stdscr, i+1, getmaxx(stdscr)-6, "| %d |", i);
            tmpTab_cursor = tmpTab_cursor->next;
            wcolor_set(stdscr, 0, NULL);
        }

        wrefresh(stdscr);

        __key = wgetch(status);
        
    }

    _L__CLEANUP_and_EXIT: {

        z__LList_delete(&sprBuffer);
        delwin(status);
        echo();
        zse_rtC_exit();
        return;
    }
}
