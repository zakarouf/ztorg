#include <stdlib.h>
#include <stdio.h>

#include "zse/zse.h"
//#define ZSE___TEST___ON

#if 0

#ifdef BUILD__WITH__TOOLS_CURSES
#  include "programs/tools_curses/zse_tools.h"
#endif
#ifdef BUILD__WITH__DEMOS_CURSES
#  include "programs/demos_curses/demo.h"
#endif

int zse_demo_screenSaver();
//int ztorg(char name[]);
//int ztorg_ray (char name[]);


#define ZSE_ARG_COMMANDS_HELP \
    "Ztorg (c) Zakarouf 2020 made with ZSE\n"\
    "\n"\
    "  -c       Show Colors\n"\
    "  -t       Tools\n"\
    "     m        Map Editor\n"\
    "     s        Sprite Editor\n"\
    "     t        Tile Editor\n"\
    "\n"\
    "  -d       Demos\n"\
    "     f        Frogger\n"\
    "     c        Cave Hunter\n"\
    "     2        2048\n"\



static int zse_main_arg_pha(int arc, char const *ar[])
{
    for (int i = 0; i < arc; ++i)
    {
        if (ar[i][0] == '-')
        {
            switch(ar[i][1])
            {
                case 'c':
                    //zse_rtC_colors_test_showall(stdscr, 0, 0);
                    //getch();
                    return 0;
                    break;
                #ifdef BUILD__WITH__TOOLS_CURSES
                case 't':
                    if (ar[i][2] == 'm')
                        zse_tool_mapEditor_st_main();
                    else if (ar[i][2] == 's')
                        zse_tool_spriteEditor_main();
                    else if (ar[i][2] == 't')
                        zse_tool_tileEditor_main ();
                    else if (ar[i][2] == 'e')
                        zse_tools_textEditor();
                    return 0;
                    break;
                #endif
                #ifdef BUILD__WITH__DEMOS_CURSES
                    case 'd':
                        if (ar[i][2] == 'f')
                            demo_frogger();
                        else if (ar[i][2] == 'c')
                            ;//demo_cave_hunter();
                        else if (ar[i][2] == '2')
                            demo_2048();
                        else if (ar[i][2] == 'p')
                            demo_perlin();
                        else if (ar[i][2] == 's')
                            zse_demo_screenSaver();
                        return 0;
                        break;
                #endif
                case 'z':

                    //ztorg((char *)ar[i+1]);
                    return 0;
                    break;
                case 'x':
                    //ztorg_ray((char*)ar[i+1]);
                    return 0;
                    break;
                case 'h':
                    //zse_rtC_exit();
                    fprintf(stdout ,ZSE_ARG_COMMANDS_HELP);
                    return 0;
                    break;
                default:
                    break;
            }


        }
    }

    return 0;
}
#ifdef ZSE_CONFIG_CURSES_ENABLE
int zse_initMainScreen_curses()
{
    if(zse_rtC_init())
    {
        return 1;
    }

    zse_rtC_color_initpairs();

    return 0;

}
#endif
#ifdef ZSE_CONFIG_SDL_ENABLE
int zse_initMainScreen_SDL()
{
    int zse_r_sdl_initscr(int x, int y);
    zse_r_sdl_initscr(600, 400);

    return 0;
}
#endif


void mainpgm(int argc, char const *argv[])
{
    #ifdef ZSE_CONFIG_SDL_ENABLE
        zse_initMainScreen_SDL();
    #endif
    #ifdef ZSE_CONFIG_CURSES_ENABLE
        zse_initMainScreen_curses();
    #endif

    //void zse_rtT_tiskTest();
    //zse_rtT_tiskTest();

    srandom(clock());


    zse_main_arg_pha(argc, argv);
    
    //int ztorg_tisk();
    //ztorg_tisk();

    
    #ifdef ZSE_CONFIG_CURSES_ENABLE
        zse_rtC_exit();
    #endif


}

#endif

#include "programs/demos_curses_new/demo.h"



int main(int argc, char const *argv[])
{
    //mainpgm(argc, argv);

    /* Vulkan */
    //void zse_rVK_init(void); zse_rVK_init();

    /* OpenGL */
    //void zse_rGL_init(void); zse_rGL_init();

    
    /* Sprite Char Editor */
    //void zse_tools_curses_spr_sChar_editor_mainloop(void);  zse_tools_curses_spr_sChar_editor_mainloop();

    /* Raylib  */
    //void ztorg_ray (const char name[]); ztorg_ray (argv[1]);
    
    /* Demos */
    //demo_clock();

    //void rpg(void); rpg();


    #ifdef ZSE___TEST___ON

        int zse___TEST(void);
        zse___TEST();

    #endif

    return 0;
}
