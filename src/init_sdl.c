#include <SDL2/SDL.h>
#include "init_sdl.h"
#include "global.h"
#include "draw_field.h"

//Initialize global game data struct thing - This is where the data is stored
GriddySDLData griddySDLData;

//Init SDL

int initSDL(void) {

	//Initalize SDL
	SDL_Init(SDL_INIT_EVERYTHING);
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Could not initialize SDL: %s", SDL_GetError());
		return true;
    }
	//Create a window - note the window already exists so I'm not making a new one so much as assigning one that already exists
	griddySDLData.fieldWindow = SDL_CreateWindow("Griddy Field Window", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 640, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
	if (!griddySDLData.fieldWindow) {
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Could not create Griddy Field Window: %s", SDL_GetError());
        SDL_Quit();
		return true;
    }
	//This is the renderer which can draw lines and other stuff
	griddySDLData.renderer = SDL_CreateRenderer(griddySDLData.fieldWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_TARGETTEXTURE); 
	//SDL_Renderer* renderer = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_TARGETTEXTURE); 
 	if (!griddySDLData.renderer) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Could not create renderer: %s", SDL_GetError());
        SDL_DestroyWindow(griddySDLData.fieldWindow);
        SDL_Quit();
		return true;
    }
	griddySDLData.screenSizeRect.x = 0;
	griddySDLData.screenSizeRect.y = 0;
	griddySDLData.screenSizeRect.w = 640;
	griddySDLData.screenSizeRect.h = 640;

	griddySDLData.fieldRect.x = 25;
	griddySDLData.fieldRect.y = 25;
	griddySDLData.fieldRect.w = 640;
	griddySDLData.fieldRect.h = 640;


	return false;
}
