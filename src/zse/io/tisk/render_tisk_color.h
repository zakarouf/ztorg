#ifndef ZSE_RENDER_STDIO_H
#define ZSE_RENDER_STDIO_H

#define zse_rtT__color_reset() \
    printf("\x1b[0m")

#define zse_rtT__colorFg_set(r, g, b) \
    printf("\x1b[38;2;%d;%d;%dm", r, g, b)

#define zse_rtT__colorBg_set(br, bg, bb) \
    printf("\x1b[48;2;%d;%d;%dm", br, bg, bb)

#define zse_rtT__colorAll_set(r, g, b, br, bg, bb) \
    printf("\x1b[38;2;%d;%d;%d;48;2;%d;%d;%dm", r, g, b, br, bg, bb)

#define zse_rtT__color256Fg_set(code) \
    printf("\x1b[38;5;%dm", code)

#define zse_rtT__color256Bg_set(code) \
    printf("\x1b[48;5;%dm", code)



/*________________________________*//*
 *          Escape Code           *
 *--------------------------------*
 *
 * "\x1b[?25h" <= Show Cursor
 * "\x1b[?25l" <= Hide Cursors
 * "\x1b[0;0H" <= Move Cursor to 0;0
 * "\x1b[2J"   <= Move Screen to new | Use for Initializing
 * "\x1b[H"    <= Move Cursor to 0;0
 */
/*________________________________*/

#endif