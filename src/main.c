#include <stdio.h>
#include "camera.h"
#include "draw_field.h"
#include "global.h"
#include "init_sdl.h"
#include "load_field_textures.h"
#include "main.h"

int main(void) {

	//This should all be compartmentalized into a main_setup();
	//SDL Init bootup	
	initSDL();
	//Setup Camera Object
	InitCameraObject();
	//Loads all textures needed in the game and stores them in variables
	LoadFieldTextures();

	//main loop
	main_loop();

	//CLEANUP
	main_cleanup();
	
	//ALL GOOD
	printf("EXIT 0\n");
	return 0;
}

void main_cleanup()
{
	//Destroy / unload everything stored in memory
	DestroyFieldTextures();
	SDL_DestroyRenderer(griddySDL_Data.renderer);
	SDL_DestroyWindow(griddySDL_Data.fieldWindow);
	SDL_Quit();
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
					//Handle Camera Translation
					case SDLK_a:
						TryTranslateCameraObjectLeft();
						break;
					case SDLK_d:
						TryTranslateCameraObjectRight();
						break;
					case SDLK_w:
						TryTranslateCameraObjectUp();
						break;
					case SDLK_s:
						TryTranslateCameraObjectDown();
						break;
					case SDLK_j:
						TryZoomCameraObjectIn();
						break;
					case SDLK_k:
						TryZoomCameraObjectOut();
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


