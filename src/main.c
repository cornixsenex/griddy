#include <stdio.h>
#include "init_sdl.h"
#include "draw_field.h"
#include "global.h"
#include "main.h"

int main(void) {

	//SDL Init bootup	
	initSDL();

	//main loop
	main_loop();

	//CLEANUP
	
	//Destroy the renderer
	SDL_DestroyRenderer(griddySDL_Data.renderer);
	//Close part 1
	SDL_DestroyWindow(griddySDL_Data.fieldWindow);
	//Close part 2
	SDL_Quit();
	//ALL GOOD
	printf("EXIT 0\n");
	return 0;
}

void main_loop() {
	int quit = false;
	while (!quit) {
		//This is a delay so it's not just flooring the CPU
		SDL_Delay(10);
		//Get input
		SDL_PollEvent(&griddySDL_Data.pollEvent);
	   //Handle input (QUIT, Keypress, Window Event...etc) 
		switch (griddySDL_Data.pollEvent.type)
		{
			case SDL_QUIT:
				quit = true;
				break;
			case SDL_KEYDOWN:
				switch (griddySDL_Data.pollEvent.key.keysym.sym) {
					case SDLK_q:
					case SDLK_ESCAPE:
						quit = true;
						break;
				}
			case SDL_WINDOWEVENT:
				switch (griddySDL_Data.pollEvent.window.event) {
					case SDL_WINDOWEVENT_RESIZED:
						//Right now just prints new window size, should call a re-draw window size thing
						HandleResizeScreen();
						break;
				}
			}
		//Draws screen
		//Should be a switch on like Screen_Type because it won't always just draw field also this should all be a seperate main_loop function
		DrawScreen(griddySDL_Data.renderer);
	
	//Return to top of Loop
	}
}


