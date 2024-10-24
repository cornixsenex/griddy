#include <stdio.h>
#include "init_sdl.h"
#include "draw_field.h"
#include "global.h"

int main(void) {
	int quit = false;

	//SDL Init bootup	
	initSDL();

	//main loop
	while (!quit)
    {
		//This is a delay so it's not just flooring the CPU
        SDL_Delay(10);
		//Get input
        SDL_PollEvent(&griddySDLData.pollEvent);
       //Handle input (QUIT, Keypress, Window Event...etc) 
		switch (griddySDLData.pollEvent.type)
        {
            case SDL_QUIT:
                quit = true;
                break;
			case SDL_KEYDOWN:
				switch (griddySDLData.pollEvent.key.keysym.sym) {
					case SDLK_q:
					case SDLK_ESCAPE:
						quit = true;
						break;
				}
			case SDL_WINDOWEVENT:
				switch (griddySDLData.pollEvent.window.event) {
					case SDL_WINDOWEVENT_RESIZED:
						//Right now just prints new window size, should call a re-draw window size thing
						HandleResizeScreen();
						break;
				}
            }
		//Draws screen
		DrawScreen(griddySDLData.renderer);
	//Return to Loop
	}

	//CLEANUP
	
	//Destroy the renderer
	SDL_DestroyRenderer(griddySDLData.renderer);
	//Close part 1
	SDL_DestroyWindow(griddySDLData.fieldWindow);
	//Close part 2
	SDL_Quit();
	//ALL GOOD
	printf("EXIT 0\n");
	return 0;
}
