#define true 1
#define false 0
#define GAME_SCREEN_TEST 0

typedef struct {
	SDL_Rect screenSizeRect;
	SDL_Event pollEvent;
	SDL_Window* fieldWindow;
	SDL_Renderer* renderer;
} GriddySDL_Data;

extern GriddySDL_Data griddySDL_Data;
