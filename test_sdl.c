#include <SDL2/SDL.h>
#include <stdio.h>

//void TestDrawField(void) {
//	//Draw ten thin lines across the thing
//	SDL_Renderer* renderer = SDL_CreateRenderer(win, -1, 0);
//	SDL_SetRenderDrawColor(renderer
//

void DrawFieldLines(SDL_Renderer *renderer, SDL_Rect fieldRect) 
{
	int x, y, i, fieldRectx, w, h;
	//do a for loop start at 0 lines drawn you need to draw x lines to have the field marked correctly
	
	//set White lines
	SDL_SetRenderDrawColor (renderer, 255, 255, 255, 255);

	//upper limit is y value of the fieldRect as defined
	y = fieldRect.y;
	//this is just the x value where the top left corner of the field is
	fieldRectx = fieldRect.x;
	//this is the total width of the field
	w = fieldRect.w;
	//This is the total height (which goes down btw) of the field	
	h = fieldRect.h; 

	//You need to draw 20 lines across the field
	for (i = 0; i < 21; i++) {
		//draw a line from a point x, y where x is the left end of the field plus i/20 of the field which is 1 / 20 or 5 units in a 100 unit wide field and y is the upper limit of the field to x, y where x is the same as above and y is the bottom limit of the field (y + h)
		x = ( fieldRectx + ( (w / 20) * i) );
		SDL_RenderDrawLine(renderer, x, y, x, y+h);
	}	
}

void RenderGriddy(SDL_Renderer *renderer)
{
	//Present the render
	SDL_RenderPresent(renderer);
}

void DrawField(SDL_Renderer *renderer, SDL_Rect fieldRect) 
{	
	int x, y, w, h;
	SDL_Rect endZone1_Rect, endZone2_Rect;
	x = fieldRect.x;
	y = fieldRect.y;
	w = fieldRect.w;
	h = fieldRect.h;
	endZone1_Rect.x = x - (w/10); 
	endZone1_Rect.y = y;
	endZone1_Rect.w = w / 10;
	endZone1_Rect.h = h;

	endZone2_Rect.x = x + w; 
	endZone2_Rect.y = y;
	endZone2_Rect.w = w / 10;
	endZone2_Rect.h = h;

	//Draw Black background
	SDL_SetRenderDrawColor (renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);
	//Draw Green Field 	
	SDL_SetRenderDrawColor (renderer, 80, 180, 100, 255);
	SDL_RenderFillRect(renderer, &fieldRect);
	//Draw End zones
	SDL_SetRenderDrawColor (renderer, 255, 255, 255, 255);
	//Left end zone
	SDL_RenderFillRect(renderer, &endZone1_Rect);
	SDL_RenderFillRect(renderer, &endZone2_Rect);
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
		75, //x
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


