#include <stdlib.h>

#include "../../zse/io/curses/curses.h"
#include "../../zse/io/curses/curses_sprite.h"

#include "../../zse/sprite/sprite_char.h"
#include "../../zse/sprite/sprite_char_draw.h"

#include "demo.h"

static void display_time(WINDOW *win ,zset__SpriteChar *nums, zset__SpriteChar *colon, int x, int y)
{
    z__int hr, min, sec;
    z__time_getLocalTime(&hr, &min, &sec);
    const z__int nextb = nums->x +1;

    zse_rtC_sprite__Print(win, x, y, nums, (hr / 10) > 0 ? hr / 10 : 0);
    x += nextb;
    zse_rtC_sprite__Print(win, x, y, nums, hr%10);
    x += nextb;

    /**/
    zse_rtC_sprite__Print(win, x-1, y, colon, 0);
    x+= nextb;
    /**/

    zse_rtC_sprite__Print(win, x, y, nums, (min / 10) > 0 ? min / 10 : 0);
    x += nextb;
    zse_rtC_sprite__Print(win, x, y, nums, min%10);
    x += nextb;

    /**/
    zse_rtC_sprite__Print(win, x-1, y, colon, 0);
    x+= nextb;
    /**/

    zse_rtC_sprite__Print(win, x, y, nums, (sec / 10) > 0 ? sec / 10 : 0);
    x += nextb;
    zse_rtC_sprite__Print(win, x, y, nums, sec%10);
    x += nextb;

}

void demo_clock(void)
{
    zse_rtC_init();
    zse_rtC_L__noecho();
    zse_rtC_L__nodelay(stdscr, true);

    zset__SpriteChar nums = zse_sprite__sChar_load("num6x5.zspr");
    zset__SpriteChar colon = zse_sprite__sChar_load("colon.zspr");

    for (int i = 0; i < 10; ++i) {
        zse_sprite__sChar_swapColors(&nums, i, 1, i+1);
    }

    while(true) {
        char k = zse_rtC_L__getch();
        switch (k) {
            case 'q': goto _L_CLEANUP_AND_EXIT; break;
            default: break;
        }

        int x = getmaxx(stdscr)/2 -(7*4), y = getmaxy(stdscr)/2 -(2);
        werase(stdscr);
        display_time(stdscr, &nums, &colon, x, y);
        refresh();
        z__time_msleep(100);
    }

    _L_CLEANUP_AND_EXIT: {
        zse_sprite__sChar_delete(&nums);
        zse_sprite__sChar_delete(&colon);
        zse_rtC_exit();
    }
}