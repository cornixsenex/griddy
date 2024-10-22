
bool SDL_init();

bool loadMedia();

void SDL_Close();

//The window we'll be rendering to
SDL_Window* gWindow = NULL;
    
//The surface contained by the window
SDL_Surface* gScreenSurface = NULL;

//The image we will load and show on the screen
SDL_Surface* gHelloWorld = NULL;

bool SDL_init()  {
	//Its Working flag
	bool sucess = true;

	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		printf("SDL could not load! SDL_ERROR: %s\n", SDL_GetError());
		sucess = false;
	} else {
		gWindow = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHWON);
		if (gWindow == NULL) {
			printf ("Window could not be created! SDL_Error: %s\n", SDL_GetError());
			sucess = false;
		} else {
			gScreenSurface = SDL_GetWindowSurface(gWindow);
		}
	}
	return sucess;
}
