#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "load_field_textures.h"
#include "global.h"

SDL_Texture* textures[TEXTURE_COUNT];

//This should just be a list of all textures I use - They should also be added to an array so it's easy to open and close them but that can wait
void LoadFieldTextures() 
{
	textures[TEXTURE_FIELD_NUM3] = IMG_LoadTexture (griddySDL_Data.renderer, "graphics/3.png");
}


void DestroyFieldTextures()
{
	int i;
	for (i = 0; i < TEXTURE_COUNT; i++) {
		SDL_DestroyTexture(textures[i]);
	}
}

	
