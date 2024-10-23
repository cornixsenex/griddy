#include <SDL2/SDL.h>
#include <stdio.h>

//void TestDrawField(void) {
//	//Draw ten thin lines across the thing
//	SDL_Renderer* renderer = SDL_CreateRenderer(win, -1, 0);
//	SDL_SetRenderDrawColor(renderer


int main(void) {
	int quit = 0;
	SDL_Event event;
	//Initalize SDL
	SDL_Init(SDL_INIT_EVERYTHING);
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Could not initialize SDL: %s", SDL_GetError());
		return 1;
    }
	//Create a window window object
	SDL_Window* win = SDL_CreateWindow("my window", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 640, SDL_WINDOW_SHOWN);

	//This is the surface which is where you render to on the window (using CPU NOT GPU)
	//SDL_Surface* winSurface = SDL_GetWindowSurface(win);

	//This is the renderer which can draw lines and other stuff
	SDL_Renderer* renderer = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_TARGETTEXTURE); 
 	if (!renderer) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Could not create renderer: %s", SDL_GetError());
        SDL_DestroyWindow(win);
        SDL_Quit();
		return 1;
    }

	//Update
	//SDL_UpdateWindowSurface(win);
	
	//Draw a rectange
	//SDL_FillRect(winSurface, NULL, SDL_MapRGB(winSurface->format, 255, 90, 120));

	//Update again	
	//SDL_UpdateWindowSurface(win);

	//Clear the screen (white screen please)
	SDL_SetRenderDrawColor (renderer, 80, 180, 100, 255);
	SDL_RenderClear(renderer);

	//Set color to black for the line drawing
	//Draw the line
	SDL_SetRenderDrawColor (renderer, 255, 255, 255, 255);
	SDL_RenderDrawLine(renderer, 10, 0, 10, 420); 
	SDL_RenderDrawLine(renderer, 20, 0, 20, 420); 
	SDL_RenderDrawLine(renderer, 30, 0, 30, 420); 
	SDL_RenderDrawLine(renderer, 40, 0, 40, 420); 
	SDL_RenderDrawLine(renderer, 50, 0, 50, 420); 
	SDL_RenderDrawLine(renderer, 60, 0, 60, 420); 
	SDL_RenderDrawLine(renderer, 70, 0, 70, 420); 
	SDL_RenderDrawLine(renderer, 80, 0, 80, 420); 
	SDL_RenderDrawLine(renderer, 90, 0, 90, 420); 
	SDL_RenderDrawLine(renderer, 100, 0, 100, 420); 

	//Present the render
	SDL_RenderPresent(renderer);

	//Wait x ms
//	SDL_Delay(4200);

	//main loop
	while (!quit)
    {
        SDL_Delay(10);
        SDL_PollEvent(&event);
 
        switch (event.type)
        {
            case SDL_QUIT:
                quit = 1;
                break;
            // TODO input handling code goes here
        }

		SDL_SetRenderDrawColor (renderer, 80, 180, 100, 255);
		SDL_RenderClear(renderer);

		SDL_SetRenderDrawColor (renderer, 255, 255, 255, 255);
		SDL_RenderDrawLine(renderer, 10, 0, 10, 420); 
		SDL_RenderDrawLine(renderer, 20, 0, 20, 420); 
		SDL_RenderDrawLine(renderer, 30, 0, 30, 420); 
		SDL_RenderDrawLine(renderer, 40, 0, 40, 420); 
		SDL_RenderDrawLine(renderer, 50, 0, 50, 420); 
		SDL_RenderDrawLine(renderer, 60, 0, 60, 420); 
		SDL_RenderDrawLine(renderer, 70, 0, 70, 420); 
		SDL_RenderDrawLine(renderer, 80, 0, 80, 420); 
		SDL_RenderDrawLine(renderer, 90, 0, 90, 420); 
		SDL_RenderDrawLine(renderer, 100, 0, 100, 420); 

		SDL_RenderPresent(renderer);
	}

	//TestDrawField();
	printf("EXIT 0");
	
	//Destroy the renderer
	SDL_DestroyRenderer(renderer);

	//Close part 1
	SDL_DestroyWindow(win);

	//Close part 2
	SDL_Quit();

	return 0;
}


