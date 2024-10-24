#include <SDL2/SDL.h>
#include <stdio.h>

#define true 1
#define false 0
#define GAME_SCREEN_TEST 0

void DrawField(SDL_Renderer *renderer, SDL_Rect fieldRect);
void RenderGriddy (SDL_Renderer *renderer);
void DrawFieldGoals(SDL_Renderer *renderer, SDL_Rect fieldRect);
//global? IDK if smart
int GameScreen = 0;

//Where to hold the fieldRect stuff - globally but inside a GameData super struct
	
	////SDL_Rect fieldRect = {
	//	75, //x
	//	50, //y
	//	500, //w
	//	250   //h
	//};

SDL_Rect fieldRect = { 75, 50, 500, 250};

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

int DrawScreen(SDL_Renderer *renderer, SDL_Rect fieldRect) {
	if (GameScreen != GAME_SCREEN_TEST) {
		printf ("GameScreen != GAME_SCREEN_TEST\n");
		return false;
	} else {
		DrawField(renderer, fieldRect);

		//DrawPlayers(renderer);

		//Last thing you do before return like actually draw it onto the screen
		RenderGriddy(renderer);
		return true;
	}
}

void DrawFieldGoals(SDL_Renderer *renderer, SDL_Rect fieldRect)
{
	int x, y, w, h, x1, y1, x2, y2, goalWidth;
	//this is the total width of the field
	x = fieldRect.x;
	//upper limit is y value of the fieldRect as defined
	y = fieldRect.y;
	//this is just the x value where the top left corner of the field is
	w = fieldRect.w;
	//This is the total height (which goes down btw) of the field	
	h = fieldRect.h; 
	//goalWidth is the length of the lines which draw the goalpost limits (it's width on this 2d field but it's 'depth' in the 3d field)
	goalWidth = w / 20;

	//Goals are at the end of the endzone which is not currently inside fieldRect (maybe fix this right idk)

	//Goals are yellow
	SDL_SetRenderDrawColor (renderer, 255, 215, 0, 255);

	//Draw Left Goals
	
	//Draw top left goal line (horizontal line that forms the north limit of the left goal)
	x1 = x - goalWidth;
	y1 = y +  (3.5 * h / 8);
	x2 = x + goalWidth;
	SDL_RenderDrawLine(renderer, x1, y1, x2, y1);

	//Draw bottom left goal line
	y2 = y + (4.5 * h / 8);
	SDL_RenderDrawLine(renderer, x1, y2, x2, y2);
	
	//Draw Right Goals
	x1 = x + w - goalWidth;
	x2 = x + w + goalWidth;
	SDL_RenderDrawLine(renderer, x1, y1, x2, y1);
	SDL_RenderDrawLine(renderer, x1, y2, x2, y2);
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
	//Right end zone
	SDL_RenderFillRect(renderer, &endZone2_Rect);
	//Draw Goals
	DrawFieldGoals(renderer, fieldRect);
	//Draw Hash Marks
	//Draw Goalines
	DrawFieldLines(renderer, fieldRect);
}

//Init SDL
//AUDIO / VIDEO / RENDERER
//CALL MAIN GAME LOOP - Handle input and output wait for exit command
//HANDLE CLOSING SDL AND EXIT 0
int main(void) {
	int quit = false;
	SDL_Event event;
	//Initalize SDL
	SDL_Init(SDL_INIT_EVERYTHING);
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Could not initialize SDL: %s", SDL_GetError());
		return 1;
    }
	//Create a window window object
	SDL_Window* win = SDL_CreateWindow("my window", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 640, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);


	//This is the renderer which can draw lines and other stuff
	SDL_Renderer* renderer = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_TARGETTEXTURE); 
 	if (!renderer) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Could not create renderer: %s", SDL_GetError());
        SDL_DestroyWindow(win);
        SDL_Quit();
		return 1;
    }
	//main loop
	while (!quit)
    {
		//This is a delay so it's not just flooring the CPU
        SDL_Delay(10);
		//Get input
        SDL_PollEvent(&event);
       //Handle input (QUIT, Keypress, Window Event...etc) 
		switch (event.type)
        {
            case SDL_QUIT:
                quit = true;
                break;
			case SDL_KEYDOWN:
				switch (event.key.keysym.sym) {
					case SDLK_q:
					case SDLK_ESCAPE:
						quit = true;
						break;
				}
			case SDL_WINDOWEVENT:
				switch (event.window.event) {
					case SDL_WINDOWEVENT_RESIZED:
						//Right now just prints new window size, should call a re-draw window size thing
						printf("Window resized to %dx%d\n", event.window.data1, event.window.data2);
						break;
				}
            }
		//Draws screen
		if ( !DrawScreen(renderer, fieldRect) ) {
			printf ("DrawScreen returned FALSE\n");
			quit = true;
		}
	//Return to Loop
	}

	//CLEANUP
	
	//Destroy the renderer
	SDL_DestroyRenderer(renderer);
	//Close part 1
	SDL_DestroyWindow(win);
	//Close part 2
	SDL_Quit();
	//ALL GOOD
	printf("EXIT 0\n");
	return 0;
}
