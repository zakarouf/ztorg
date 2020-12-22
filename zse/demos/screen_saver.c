#include "../zse.h"


static int getTime(int *h, int *m, int *s)
{

  static time_t tCurrentTime;
  static struct tm *timeinfo;
  time(&tCurrentTime);
  timeinfo = localtime(&tCurrentTime);
  *h = timeinfo->tm_hour;
  *m = timeinfo->tm_min;
  *s = timeinfo->tm_sec;

  return 0;
}

static int printTime(SPRITES_t *sprNumbers, SPRITES_t *sprColon )
{
  int hour, min, sec;
  getTime(&hour, &min, &sec);

  zse_u8_t u8_Xskip = sprNumbers[0].X+1 ;

  int x = getmaxx(stdscr)/2 -(7*4), y = getmaxy(stdscr)/2 -(3);

  zse_rtC_spritePrintf(stdscr, x, y, &sprNumbers[(hour / 10) > 0 ? hour / 10 : 0], 0);
  x += u8_Xskip;
  zse_rtC_spritePrintf(stdscr, x, y, &sprNumbers[hour%10], 0);
  x += u8_Xskip;

  zse_rtC_spritePrintf(stdscr, x, y, sprColon, 0);
  x += u8_Xskip;

  zse_rtC_spritePrintf(stdscr, x, y, &sprNumbers[(min / 10) > 0 ? min / 10 : 0], 0);
  x += u8_Xskip;
  zse_rtC_spritePrintf(stdscr, x, y, &sprNumbers[min%10], 0);
  x += u8_Xskip;

  zse_rtC_spritePrintf(stdscr, x, y, sprColon, 0);
  x += u8_Xskip;

  zse_rtC_spritePrintf(stdscr, x, y, &sprNumbers[(sec / 10) > 0 ? sec / 10 : 0], 0);
  x += u8_Xskip;
  zse_rtC_spritePrintf(stdscr, x, y, &sprNumbers[sec%10], 0);
  x += u8_Xskip;




  return 0;
}

int zse_demo_screenSaver()
{
  SPRITES_t *sprNumbers = malloc(sizeof(SPRITES_t) *10);
  sprNumbers[0] = zse_sprites_sin_load("0.zspr");
  sprNumbers[1] = zse_sprites_sin_load("1.zspr");
  sprNumbers[2] = zse_sprites_sin_load("2.zspr");
  sprNumbers[3] = zse_sprites_sin_load("3.zspr");
  sprNumbers[4] = zse_sprites_sin_load("4.zspr");
  sprNumbers[5] = zse_sprites_sin_load("5.zspr");
  sprNumbers[6] = zse_sprites_sin_load("6.zspr");
  sprNumbers[7] = zse_sprites_sin_load("7.zspr");
  sprNumbers[8] = zse_sprites_sin_load("8.zspr");
  sprNumbers[9] = zse_sprites_sin_load("9.zspr");

  SPRITES_t sprColon = zse_sprites_sin_load("colon.zspr");


  nodelay(stdscr, TRUE);

  while(TRUE)
  {
    switch(getch())
    {
      case 'q':
        nodelay(stdscr, FALSE);
        return 0;
        break;
      default:
        break;
    }
    
    clear();
    printTime(sprNumbers, &sprColon);
    refresh();
    sleep(1);

  }



  return 0;
}

