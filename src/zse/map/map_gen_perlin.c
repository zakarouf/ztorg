/*-----------------------------------------------
    Generate Perlin Noise.
/-----------------------------------------------/
    - Courtesy of nowl (https://gist.github.com/nowl/828013)

    - Code updated by deeemmell 
        (https://gist.github.com/deeemmell)
        to support negetive x,y coordinate
    
-----------------------------------------------*/
//---------------------------------------------//

#include "gen.h"

static z__i64 _zse_mapgen_perlin_SEED;

static const z__u8  HASH[] = {
    208,34,231,213,32,248,233,56,161,78,24,140,71,48,140,254,245,255,247,247,40,
    185,248,251,245,28,124,204,204,76,36,1,107,28,234,163,202,224,245,128,167,204,
    9,92,217,54,239,174,173,102,193,189,190,121,100,108,167,44,43,77,180,204,8,81,
    70,223,11,38,24,254,210,210,177,32,81,195,243,125,8,169,112,32,97,53,195,13,
    203,9,47,104,125,117,114,124,165,203,181,235,193,206,70,180,174,0,167,181,41,
    164,30,116,127,198,245,146,87,224,149,206,57,4,192,210,65,210,129,240,178,105,
    228,108,245,148,140,40,35,195,38,58,65,207,215,253,65,85,208,76,62,3,237,55,89,
    232,50,217,64,244,157,199,121,252,90,17,212,203,149,152,140,187,234,177,73,174,
    193,100,192,143,97,53,145,135,19,103,13,90,135,151,199,91,239,247,33,39,145,
    101,120,99,3,186,86,99,41,237,203,111,79,220,135,158,42,30,154,120,67,87,167,
    135,176,183,191,253,115,184,21,233,58,129,233,142,39,128,211,118,137,139,255,
    114,20,218,113,154,27,127,246,250,1,8,198,250,209,92,222,173,21,88,102,219
};

static int _perlin_noise2(int x, int y)
{
    int  yindex = (y + _zse_mapgen_perlin_SEED) & 0xFF;
    if (yindex < 0)
        yindex += 256;
    int  xindex = (HASH[yindex] + x) & 0xFF;
    if (xindex < 0)
        xindex += 256;
    const int  result = HASH[xindex];
    return result;
}

ZSE__INLINE double _perlin_lin_inter(double x, double y, double s)
{
    return x + s * (y-x);
}

ZSE__INLINE double _perlin_smooth_inter(double x, double y, double s)
{
    return _perlin_lin_inter( x, y, s * s * (3-2*s) );
}

static double _perlin_noise2d(double x, double y)
{
    const int  x_int = floor( x );
    const int  y_int = floor( y );
    const double  x_frac = x - x_int;
    const double  y_frac = y - y_int;
    const int  s = _perlin_noise2( x_int, y_int );
    const int  t = _perlin_noise2( x_int+1.0f, y_int );
    const int  u = _perlin_noise2( x_int, y_int+1.0f );
    const int  v = _perlin_noise2( x_int+1.0f, y_int+1.0f );
    const double  low = _perlin_smooth_inter( s, t, x_frac );
    const double  high = _perlin_smooth_inter( u, v, x_frac );
    const double  result = _perlin_smooth_inter( low, high, y_frac );
    return result;
}



void zse_map__genP2d_SetNoiseSeed(int seed)
{
    _zse_mapgen_perlin_SEED = seed;
}
int zse_map__genP2d_GetNoiseSeed(void)
{
    return _zse_mapgen_perlin_SEED;
}

//----------------------------------------------------------
// Returns single double val according to x,y cord
// Example : foo_array[y][x] = zse_map_gen2d_get_solo(x, y, 0.1, 4)
double zse_map__genP2d_getSolo(double x, double y, double freq, int depth)
{
    double  xa = x*freq;
    double  ya = y*freq;
    double  amp = 1.0f;
    double  fin = 0.0f;
    double  div = 0.0f;
    for (int i=0; i<depth; i++)
    {
        div += 256 * amp;
        fin += _perlin_noise2d( xa, ya ) * amp;
        amp /= 2;
        xa *= 2;
        ya *= 2;
    }
    return fin/div;
}
