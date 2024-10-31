#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "load_field_textures.h"
#include "global.h"

SDL_Texture* textures[TEXTURE_COUNT];

//This should just be a list of all textures I use - They should also be added to an array so it's easy to open and close them but that can wait
void LoadFieldTextures() 
{
	textures[TEXTURE_FIELD_NUM1] = IMG_LoadTexture (griddySDL_Data.renderer, "graphics/1.png");
	textures[TEXTURE_FIELD_NUM2] = IMG_LoadTexture (griddySDL_Data.renderer, "graphics/2.png");
	textures[TEXTURE_FIELD_NUM3] = IMG_LoadTexture (griddySDL_Data.renderer, "graphics/3.png");
	textures[TEXTURE_FIELD_NUM4] = IMG_LoadTexture (griddySDL_Data.renderer, "graphics/4.png");
	textures[TEXTURE_FIELD_NUM5] = IMG_LoadTexture (griddySDL_Data.renderer, "graphics/5.png");

	textures[TEXTURE_FIELD_NUM0] = IMG_LoadTexture (griddySDL_Data.renderer, "graphics/0.png");
}


void DestroyFieldTextures()
{
	int i;
	for (i = 0; i < TEXTURE_COUNT; i++) {
		SDL_DestroyTexture(textures[i]);
	}
}

	
