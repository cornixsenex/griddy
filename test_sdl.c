#include <SDL2/SDL.h>
#include <stdio.h>


void main(void) {
	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_Window* win = SDL_CreateWindow("my window", 100, 100, 640, 640, SDL_WINDOW_SHOWN);
	SDL_Surface* winSurface = SDL_GetWindowSurface(win);

	SDL_UpdateWindowSurface(win);

	SDL_FillRect(winSurface, NULL, SDL_MapRGB(winSurface->format, 255, 90, 120));
	
	SDL_UpdateWindowSurface(win);

	SDL_Delay(4200);

	SDL_DestroyWindow(win);

	SDL_Quit();
	
}


