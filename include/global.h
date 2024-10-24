#define true 1
#define false 0
#define GAME_SCREEN_TEST 0

typedef struct {
	SDL_Rect screenSizeRect;
	SDL_Rect fieldRect;
	SDL_Event pollEvent;
	SDL_Window* fieldWindow;
	SDL_Renderer* renderer;
} GriddySDLData;

extern GriddySDLData griddySDLData;
