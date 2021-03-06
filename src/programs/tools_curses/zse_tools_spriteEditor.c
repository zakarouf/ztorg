/*-----------------------------------------------------
            Sprite Editer For ZSE
//---------------------------------------------------//

    +-----------------------------------------------+
    |The sprites used for zse is in custom format   |
    |single sprite is stored as .zspr format        |
    +-----------------------------------------------+
    
    TODO: Complete Sequence
    
-----------------------------------------------------*/

#include <stdlib.h>

#include "zse_tools.h"
#include "../../zse/io/curses/curses.h"


#define ZSE_T_SPRSR_OP_COLORS    0x1
#define ZSE_T_SPRSR_OP_TRANSENAB 0x2
#define ZSE_T_SPRSR_OP_TRANSSHOW 0x4

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

typedef struct _ZSE_SPRITE_BUFFER
{
    SPRITES_t spr;
    zse_i8 dirty;


}zse_spriteBuffer_t;

static int _zse_tools_spriteEditor_spriteTest(SPRITES_t *spr)
{
    clear();
    printw("X -> %d\nY -> %d\nFrames -> %d\n", spr->X, spr->Y, spr->frames);
    printw("MAX Sequence %d\nPrinting Sequence\n", spr->seqMax);

    for (int i = 0; i < spr->seqMax; ++i)
    {
        addstr("->");
        for (int j = 0; j < spr->_seqEnd[i]; ++j)
        {
            printw(" %d", spr->seqData[i][j]);
        }
        printw(" | %d\n", spr->_seqEnd[i]);
    }

    refresh();
    return OK;

}

static void _render_showSeditorNormal
(
    WINDOW *win,
    sprite_data_t *chunk,
    char options,
    const int Xsize,
    const int Ysize,
    const int Zsize,
    int x,
    int y,
    int z,
    const int resizeX,
    const int resizeY
)
{
    const int screensizeX = getmaxx(win) -(resizeX);
    const int screensizeY = getmaxy(win) -(resizeY);

    int cursor_y = 0, cursor_x = 0;

    int i = y - (int)(screensizeY>>1) -1, j;

    int end_i = y + (int)(screensizeY>>1) +1;
    int end_j = x + (int)(screensizeX>>1) +1;

    if (end_i >= Ysize) {end_i = Ysize; i = Ysize - screensizeY -1;}
    if (i < 0) {
        i = 0;
        if(screensizeY <= Ysize){
            end_i = screensizeY+1;
        }
    }

    const int lower_z = (z-1>=0)? z-1:0;
    uint8_t lowerzc;

    for (; i < end_i; ++i)
    {
        j = x - (int)(screensizeX>>1) -1;
        if (end_j >= Xsize) {end_j = Xsize; j = Xsize - screensizeX -1;}
        if (j < 0) {j = 0;
            if(screensizeX <= Xsize){
                end_j = screensizeX+1;
            }
        }
        lowerzc = chunk[zse_xyz3Dto1D(j, i, lower_z, Xsize, Ysize)]&0xff;

        wmove(win ,cursor_y, cursor_x);

        for (; j < end_j; ++j)
        {

            if ((chunk[zse_xyz3Dto1D(j, i, z, Xsize, Ysize)]&0xff) != 0xff) // IF plot point is not transperant (0xff)
            {
                if(!(options&ZSE_T_SPRSR_OP_COLORS))
                {

                    if(lowerzc == (chunk[zse_xyz3Dto1D(j, i, z, Xsize, Ysize)]&0xff)) // Check is Lower Z value and Z value is Same(Not Counting SPACE)
                    {
                        wattrset(win ,COLOR_PAIR(1));
                        waddch(win ,chunk[zse_xyz3Dto1D(j, i, z, Xsize, Ysize)]&0xFF);
                    }
                    else
                    {
                        waddch(win ,chunk[zse_xyz3Dto1D(j, i, z, Xsize, Ysize)]&0xFF);
                    }

                }

                else
                {
                    //Colormode;

                    wattrset(win ,COLOR_PAIR(chunk[zse_xyz3Dto1D(j, i, z, Xsize, Ysize)]>>8));
                    waddch(win ,chunk[zse_xyz3Dto1D(j, i, z, Xsize, Ysize)]&255);
                }
            }

            else
            {
                wattrset(win, COLOR_PAIR(7));

                if (options&ZSE_T_SPRSR_OP_TRANSENAB)
                {

                    
                    for (int l = lower_z; l >= 0; --l)
                    {
                        if ((chunk[zse_xyz3Dto1D(j, i, l, Xsize, Ysize)]&255) == 0xff)
                        {
                            continue;
                        }
                        else
                        {
                            if (options&ZSE_T_SPRSR_OP_TRANSSHOW)
                            {
                                wattrset(win ,COLOR_PAIR(0xff) | A_REVERSE);      
                            }
                            else
                            {
                                wattrset(win ,COLOR_PAIR(chunk[zse_xyz3Dto1D(j, i, l, Xsize, Ysize)]>>8));
                            }
                            
                            waddch(win ,chunk[zse_xyz3Dto1D(j, i, l, Xsize, Ysize)]&0xff);
                            break;
                        }
                    }
                }
                else
                {
                    waddch(win, ' ');
                }
            }


            wattrset(win, A_NORMAL);

            if(j == x && i == y)
            {
                waddstr(win, "\b@");
            }

        }
        wprintw(win, "| %d", i);
        cursor_y++;
    }

    // Add Cursor
    wrefresh(win);
}

static int _zse_sprites_edtior_func_CopyFrame(sprite_data_t* data, int fromframe,int atframe, int xsize, int ysize, int zsize)
{
    if(fromframe < 0 || fromframe >= zsize)
    {
        return 1;
    }
    for (int i = 0; i < xsize*ysize; ++i)
    {
        data[atframe*xsize*ysize +i] = data[fromframe*xsize*ysize +i];
    }

    return 0;
}

static void _zse_tools_spritesEditor_render_showframesSequences(WINDOW *win, int x, int y, int cur ,sequence_data_t seqEnd, sequence_data_t* seqData)
{
    wmove(win ,y, x);
    waddch(win ,'[');

    for (int i = 0; i < seqEnd; ++i)
    {
        if (i == cur){
            attron(A_REVERSE);    
            wprintw(win, " %d", seqData[i]);
            attroff(A_REVERSE);
        }
        else
        {
            wprintw(win, " %d", seqData[i]);
        }

        
    }
    waddch(win, ']');
};

int zse_sprite_reallocSingleSequence(SPRITES_t *spr, int seqCur, int newlen)
{
    if (newlen <= 0)
        return -1;

    void *a = realloc(spr->seqData[seqCur], sizeof(sequence_data_t) * newlen);

    if (a != NULL)
    {
        spr->seqData[seqCur] = a;
        spr->_seqEnd[seqCur] = newlen;
    }


    return 0;
}

static int _zse_tools_spriteEditor_createSequence(SPRITES_t *spr, int renOP)
{
    static int seqs_Cur = 0;
    int seqFrameCur = 0;
    int framelayerCur = 0;
    

    while(TRUE)
    {
        switch(getch())
        {
            case 'a':
                if(seqFrameCur > 0){
                    seqFrameCur--;
                }
                break;

            case 'd':
                if(seqFrameCur < spr->_seqEnd[seqs_Cur]-1){
                    seqFrameCur++;
                }
                break;

            case '=':
                zse_sprite_reallocSingleSequence(&spr[0], seqs_Cur, spr->_seqEnd[seqs_Cur] + 1);
                spr->seqData[seqs_Cur][spr->_seqEnd[seqs_Cur] - 1] = 0;
                break;
            case '-':
                zse_sprite_reallocSingleSequence(&spr[0], seqs_Cur, spr->_seqEnd[seqs_Cur] - 1);
                break;

            case 'z':
                if(framelayerCur > 0)
                {
                    framelayerCur--;
                }
                break;
            case 'x':
                if(framelayerCur < spr->frames-1)
                {
                    framelayerCur++;
                }
                break;

            case 's':
                spr->seqData[seqs_Cur][seqFrameCur] = framelayerCur;
                break;



            case 'c':
                seqs_Cur = zse_rtC_getint();
                seqs_Cur = (seqs_Cur >= spr->seqMax || seqs_Cur < 0 ? 0 : seqs_Cur);

                break;
            case '`':
                return 0;
            default:break;
        }
        wclear(stdscr);

        _zse_tools_spritesEditor_render_showframesSequences(stdscr, 0, getmaxy(stdscr) - 3, seqFrameCur, spr->_seqEnd[seqs_Cur], spr->seqData[seqs_Cur]);
        mvwprintw(stdscr, getmaxy(stdscr)-2, 0, "Frame : %d  SeqN : %d", framelayerCur, seqFrameCur);
        zse_rtC_spritePrintf(stdscr, 0, 0, spr, framelayerCur);

        wrefresh(stdscr);
    }
}

static int _zse_sprites_edtior(SPRITES_t *spr)
{

    char Toggle[2][4] = {"Off", "On"};
    size_t sessions = 1;

    BRUSH_t brush = {0, 0, 0, '.', 0, 0};

    char name[ZSE_MAX_FILENAME_SIZE];
    char tmp_op;
    char r_options = ZSE_T_SPRSR_OP_COLORS | ZSE_T_SPRSR_OP_TRANSENAB | ZSE_T_SPRSR_OP_TRANSSHOW;
    short brush_colo = 0x01;
    // NOTE: z is the frame

    WINDOW * status = newwin(5, getmaxx(stdscr), getmaxy(stdscr) - 5, 0);

    wclear(stdscr);
    _render_showSeditorNormal(stdscr, spr->plot, r_options, spr->X, spr->Y, spr->frames, brush.pos.x, brush.pos.y, brush.pos.z, 0, 0);
    while(TRUE)
    {

        switch(getch()){
            case 'w':if(brush.pos.y -1 >= 0)brush.pos.y--;
                break;
            case 's':if(brush.pos.y +1 < spr->Y)brush.pos.y++;
                break;
            case 'a':if(brush.pos.x -1 >= 0)brush.pos.x--;
                break;
            case 'd':if(brush.pos.x +1 < spr->X)brush.pos.x++;
                break;
            case 'x':
                if(brush.pos.z +1 < spr->frames){brush.pos.z++;}
                break;
            case 'z':
                if(brush.pos.z -1 >= 0){brush.pos.z--;}
                break;


            // Brush
            case 'b':
                echo();
                mvwprintw(status, 4, 0 ,"Brush Size >>");wrefresh(status);
                mvwscanw(status, 4, 14 ,"%hhd" , &brush.size);
                noecho();
                break;
            case 'v':
                brush.toggle ^= 1;
                break;
            case 'c':
                brush.ink &= 0xFF00;
                brush.ink |= getch();
                break;
            case 'p':
                brush.ink &= 0xFF00;
                brush.ink |= spr->plot[zse_xyz3Dto1D(brush.pos.x, brush.pos.y, brush.pos.z, spr->X, spr->Y)]&0x00FF;
                break;

            // Colour Stuff
            case 'e':
                brush.ink &= 0x00FF;    // Clear any Previous color
                brush.ink |= (brush_colo * 0x100); // Apply color
                break;
            case 'l':
                brush.ink &= 0x00FF;
                brush.ink |= brush.ink |= spr->plot[zse_xyz3Dto1D(brush.pos.x, brush.pos.y, brush.pos.z, spr->X, spr->Y)]&0xFF00;
                break;
            case '-':
                brush_colo --;
                if(brush_colo < 0){brush_colo = COLORS -1;}
                break;
            case '=':
                brush_colo ++;
                if(brush_colo > COLORS){brush_colo = 0;}
                break;
            case '_':
                brush_colo -= 6;
                if(brush_colo < 0){brush_colo = COLORS -1;}
                break;
            case '+':
                brush_colo += 6;
                if(brush_colo > COLORS){brush_colo = 0;}
                break;
            case 127: // Delete
                zse_rtC_colors_test_showall(stdscr, getmaxx(stdscr)/5 -(6*3), 0);
                getch();
                break;


            // Canvas Manupilation
            case 'h':
                // Realloc Frames
                break;
            case 'r':
                // Edit dt
                mvwscanw(status, 4, 0 ,"%f" , &spr->dt);
                break;

            // Commands
            case ':':
                tmp_op = getch();

                // Enable To Render Colours
                if(tmp_op == 'o')r_options ^= ZSE_T_SPRSR_OP_COLORS;
                // Enable Transparency
                if(tmp_op == 'p')r_options ^= ZSE_T_SPRSR_OP_TRANSENAB;
                // Make Transparent stand out
                if(tmp_op == 'i')r_options ^= ZSE_T_SPRSR_OP_TRANSSHOW;

                // Copy Last Frame
                if(tmp_op == 'c'){_zse_sprites_edtior_func_CopyFrame(spr->plot, brush.pos.z-1, brush.pos.z, spr->X, spr->Y, spr->frames);}

                //Copy From Selected Frame
                if(tmp_op == 'f')
                {
                    int frame;
                    wscanw(status, "%d", &frame);
                    _zse_sprites_edtior_func_CopyFrame(spr->plot, frame, brush.pos.z, spr->X, spr->Y, spr->frames);
                }

                // Save Sprite
                if(tmp_op == 's')
                {
                    echo();
                    mvwprintw(status, 3, 0 ,"Save Sprite As >> ");wrefresh(status);
                    wgetstr(status,name);
                    noecho();
                    zse_sprites_sin_export(spr, name);
                }

                // Slide Show Sprite
                if(tmp_op == ' ')zse_rtC_spritePrintAll(stdscr ,0, 0, spr, 0, spr->frames);

                // Select Transparent Char
                if(tmp_op == 'x')brush.ink |= 0xFF;

                // Help
                if(tmp_op == 'h')
                {
                    mvwprintw(stdscr, 0,0, "%s", ZSE_T_SPRSR_OP_HELPTEXT);
                    wgetch(stdscr);
                }

                // Sequence Edit
                if (tmp_op == 'S')
                {
                    _zse_tools_spriteEditor_createSequence(spr, r_options);
                }

                break;



            case '!':
                //sessions++;
                //spr = realloc(spr, sessions);

                break;
            case '4':
                _zse_tools_spriteEditor_spriteTest(spr);
                getch();
                break;

            // Exit
            case '`':
                zse_delete_sprites_ptr(spr);
                return 0;
                break;
            default:
                break;
        }

        if(brush.toggle)
        {
            spr->plot[zse_xyz3Dto1D(brush.pos.x, brush.pos.y, brush.pos.z, spr->X, spr->Y)] = brush.ink; 
        }

        mvwprintw(status, 0, 0,"Brush[%3s] -> %c {%s} :: %d =Color={%hi}"
            , Toggle[brush.toggle], brush.ink , "NONE", brush.size, brush_colo);

        wattrset(status, COLOR_PAIR(brush_colo));
        waddstr(status,"##  \n");
        wattrset(status, COLOR_PAIR(A_NORMAL));


        mvwprintw(status, 1, 0, "POS [%hd,%hd] Frame - %3d/%3d Color No. %d"
            , brush.pos.x, brush.pos.y, brush.pos.z, spr->frames-1, spr->plot[zse_xyz3Dto1D(brush.pos.x, brush.pos.y, brush.pos.z, spr->X, spr->Y)]>>8);

        mvwprintw(status, 2, 0, "Show: Colors %d  TransEnable %d  TransShow %d", r_options&ZSE_T_SPRSR_OP_COLORS? 1:0, r_options&ZSE_T_SPRSR_OP_TRANSENAB? 1:0, r_options&ZSE_T_SPRSR_OP_TRANSSHOW? 1:0);

        wclear(stdscr);
        _render_showSeditorNormal(stdscr, spr->plot, r_options, spr->X, spr->Y, spr->frames, brush.pos.x, brush.pos.y, brush.pos.z, 0, 0);
        wrefresh(status);

    }



    return 0;
}

static int _zse_sprite_newCreateMenu(SPRITES_t *spr)
{
    
    
    while(TRUE)
    {
        clear();
        printw("Create (N)ew Sprite Or (O)pen A Sprite file || (Q)uit");
        char yes = getch();
        clear();

        if(yes == 'N')
        {
            mvprintw(0, 0, "Get X           : ");
            mvscanw(0, 16, "%hd", &spr->X);

            mvprintw(1, 0, "Get Y           : ");
            mvscanw(1, 16, "%hd", &spr->Y);

            mvprintw(2, 0, "Get Frames      : ");
            mvscanw(2, 16, "%d", &spr->frames);

            mvprintw(3, 0, "Get DeltaTime   : ");
            mvscanw(3, 16, "%f", &spr->dt);

            mvprintw(4, 0, "Get Max Sequence: ");
            mvscanw(4, 16, "%hd", &spr->seqMax);


            spr->plot = malloc(sizeof(sprite_data_t) * spr->X * spr->Y * spr->frames);
            
            for (int i = 0; i < spr->X*spr->Y*spr->frames; ++i)
            {
                spr->plot[i] = ' ';
            }
            

            spr->_seqEnd = malloc(sizeof(sequence_data_t) * spr->seqMax);
            
            for (int i = 0; i < spr->seqMax; ++i)
            {
                spr->_seqEnd[i] = 2;
            }
                

            spr->seqData = zse_sprite_malloc_sequence_data(spr->_seqEnd, spr->seqMax);


            return 0;
        }
        else if(yes == 'O')
        {

            char *name = malloc(sizeof(char) * ZSE_MAX_FILENAME_SIZE + sizeof(SPRITES_SINGLE_EXT));
            
            
            StringLines_t fnames = zse_dir_getfnames(SPRITES_PARENTDIR);

            zse_rtC_selectListS(stdscr, 0, 0, fnames.lines, fnames.y, name);
            z__StringLines_destroy(&fnames);


            *spr = zse_sprites_sin_load(name);
            free(name);

            _zse_tools_spriteEditor_spriteTest(spr);
            getch();

            return 0;
        }
        else if(yes == 'Q')
        {
            return 1;
        }
    }


}




int zse_tool_spriteEditor_main()
{
    SPRITES_t *spr = malloc(sizeof(SPRITES_t));
    
    if(_zse_sprite_newCreateMenu(spr))
        return 0;

    _zse_sprites_edtior(spr);

    return 0;
}