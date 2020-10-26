#ifndef ZSE_RENDER_STDIO_H
#define ZSE_RENDER_STDIO_H

#include <stdio.h>

#define zse_rs_color_reset() \
    printf("\x1b[0m")

#define zse_rs_colorFg_set(r, g, b) \
    printf("\x1b[38;2;%d;%d;%dm", r, g, b)

#define zse_rs_colorBg_set(br, bg, bb) \
    printf("\x1b[48;2;%d;%d;%dm", br, bg, bb)

#define zse_rs_colorAll_set(r, g, b, br, bg, bb) \
    printf("\x1b[38;2;%d;%d;%d;48;2;%d;%d;%dm", r, g, b, br, bg, bb)

#define zse_rs_color256Fg_set(code) \
    printf("\x1b[38;5;%dm", code)

#define zse_rs_color256Bg_set(code) \
    printf("\x1b[48;5;%dm", code)



#endif