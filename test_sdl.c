#include <SDL2/SDL.h>
#include <stdio.h>

//void TestDrawField(void) {
//	//Draw ten thin lines across the thing
//	SDL_Renderer* renderer = SDL_CreateRenderer(win, -1, 0);
//	SDL_SetRenderDrawColor(renderer
//

int DrawFieldLines(SDL_Renderer *renderer, SDL_Rect fieldRect) 
{
	int x, y, i, fieldRectx, w, h;
	//do a for loop start at 0 lines drawn you need to draw x lines to have the field marked correctly
	
	//Draw the lines
	//White lines
	SDL_SetRenderDrawColor (renderer, 255, 255, 255, 255);

	y = fieldRect.y;
	fieldRectx = fieldRect.x;
	w = fieldRect.w;
	h = fieldRect.h; 

	for (i = 0; i < 21; i++) {
		x = ( fieldRectx + ( (w / 20) * i) );
		SDL_RenderDrawLine(renderer, x, y, x, y+h);
	}	
	
	//SDL_RenderDrawLine(renderer, 105, 100, 105, 350);
	
	return 0;
}

int RenderGriddy(SDL_Renderer *renderer)
{
	//Present the render
	SDL_RenderPresent(renderer);
	return 0;
}


int DrawField(SDL_Renderer *renderer, SDL_Rect fieldRect) 
{	
	//Draw Black background
	SDL_SetRenderDrawColor (renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);
	//Draw Green Field 	
	SDL_SetRenderDrawColor (renderer, 80, 180, 100, 255);
	SDL_RenderFillRect(renderer, &fieldRect);

	//SDL_RenderDrawLine(renderer, 10, 0, 10, 420); 
	//SDL_RenderDrawLine(renderer, 20, 0, 20, 420); 
	//SDL_RenderDrawLine(renderer, 30, 0, 30, 420); 
	//SDL_RenderDrawLine(renderer, 40, 0, 40, 420); 
	//SDL_RenderDrawLine(renderer, 50, 0, 50, 420); 
	//SDL_RenderDrawLine(renderer, 60, 0, 60, 420); 
	//SDL_RenderDrawLine(renderer, 70, 0, 70, 420); 
	//SDL_RenderDrawLine(renderer, 80, 0, 80, 420); 
	//SDL_RenderDrawLine(renderer, 90, 0, 90, 420); 
	//SDL_RenderDrawLine(renderer, 100, 0, 100, 420); 

	return 0;
}

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

	SDL_Rect fieldRect = {
		50, //x
		50, //y
		500, //w
		250   //h
	};

	// SURFACES
	
	//Update
	//SDL_UpdateWindowSurface(win);
	
	//Draw a rectange
	//SDL_FillRect(winSurface, NULL, SDL_MapRGB(winSurface->format, 255, 90, 120));

	//Update again	
	//SDL_UpdateWindowSurface(win);

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

		DrawField(renderer, fieldRect);
		DrawFieldLines(renderer, fieldRect);
		RenderGriddy(renderer);
	}

	//Destroy the renderer
	SDL_DestroyRenderer(renderer);

	//Close part 1
	SDL_DestroyWindow(win);

	//Close part 2
	SDL_Quit();
	printf("EXIT 0");

	return 0;
}


