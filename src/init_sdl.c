#include <SDL2/SDL.h>
#include "init_sdl.h"
#include "global.h"
#include "draw_field.h"

//Initialize global game data struct thing - This is where the window data is stored
GriddySDL_Data griddySDL_Data;

//Init SDL
int initSDL(void) {

	//Initalize SDL
	SDL_Init(SDL_INIT_EVERYTHING);
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Could not initialize SDL: %s", SDL_GetError());
		return true;
    }
	//Create a window - note the window already exists so I'm not making a new one so much as assigning one that already exists
	griddySDL_Data.fieldWindow = SDL_CreateWindow("Griddy Field Window", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 640, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
	if (!griddySDL_Data.fieldWindow) {
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Could not create Griddy Field Window: %s", SDL_GetError());
        SDL_Quit();
		return true;
    }
	//This is the renderer which can draw lines and other stuff
	griddySDL_Data.renderer = SDL_CreateRenderer(griddySDL_Data.fieldWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_TARGETTEXTURE); 
	//SDL_Renderer* renderer = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_TARGETTEXTURE); 
 	if (!griddySDL_Data.renderer) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Could not create renderer: %s", SDL_GetError());
        SDL_DestroyWindow(griddySDL_Data.fieldWindow);
        SDL_Quit();
		return true;
    }
	//Default screen size is 640 x 640
	griddySDL_Data.screenSizeRect.x = 0;
	griddySDL_Data.screenSizeRect.y = 0;
	griddySDL_Data.screenSizeRect.w = 640;
	griddySDL_Data.screenSizeRect.h = 640;

	return false;
}


