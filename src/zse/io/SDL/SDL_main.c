#include <SDL2/SDL.h>

#include "SDL.h"


#define bool unsigned char
#define true 1
#define false 0

//The window we'll be rendering to
static SDL_Window* gWindow = NULL;
    
//The surface contained by the window
static SDL_Surface* gScreenSurface = NULL;

//The image we will load and show on the screen
static SDL_Surface* gHelloWorld = NULL;

bool loadMedia()
{
    //Loading success flag
    bool success = true;

    //Load splash image
    gHelloWorld = SDL_LoadBMP( "hello.bmp" );
    if( gHelloWorld == NULL )
    {
        printf( "Unable to load image %s! SDL Error: %s\n", "02_getting_an_image_on_the_screen/hello_world.bmp", SDL_GetError() );
        success = false;
    }

    return success;
}


static bool init()
{
    //Initialization flag
    bool success = true;

    //Initialize SDL
    if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
    {
        printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
        success = false;
    }
    else
    {
        //Create window
        gWindow = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1000, 800, SDL_WINDOW_SHOWN );
        if( gWindow == NULL )
        {
            printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
            success = false;
        }
        else
        {
            //Get window surface
            gScreenSurface = SDL_GetWindowSurface( gWindow );
        }
    }

    return success;
}

void close()
{
    //Deallocate surface
    SDL_FreeSurface( gHelloWorld );
    gHelloWorld = NULL;

    //Destroy window
    SDL_DestroyWindow( gWindow );
    gWindow = NULL;

    //Quit SDL subsystems
    SDL_Quit();
}

int zse_r_sdl_initscr(int x, int y)
{
	init();
//Load media
    if( !loadMedia() )
    {
		printf( "Failed to load media!\n" );
    }
    else
    {
            //Apply the image
    	SDL_BlitSurface( gHelloWorld, NULL, gScreenSurface, NULL );
    	SDL_UpdateWindowSurface( gWindow );
    	   	//Wait two seconds
        SDL_Delay( 2000 );
	}

	close();

	return 0;
}