#include <SDL2/SDL.h>

typedef enum {
	FIELD_TYPE_GRIDDY,
	FIELD_TYPE_FOOTY,
	FIELD_TYPE_NONE
} FieldType;

typedef struct {
	FieldType FieldType;
	float total_layout_length;
	float total_layout_width;
} FieldDimension;

typedef struct {
	FieldDimension base;
	float fieldLength;
	float fieldWidth;
	float endzone_length;
	float sideline_width;
	float bench_area_length; //25 to 25 lines that's 50 yards = 150 feet
	float bench_area_width;
	float perimeter_width;
	float hashSpaceWidth;
	float hashMarkLength;
	float goalWidth;
	float goalDepth;
	float numberHeight;
	float numberWidth;
	float numberMargin;
	//int bench_area_length;
} FieldDimension_Griddy;

typedef struct {
	FieldDimension base;
	float fieldWidth;
	float fieldLength;
	//etc
} FieldDimension_Footy;

extern FieldDimension_Griddy FieldDimension_Griddy_Default;

int DrawScreen(SDL_Renderer *renderer); 

void RenderGriddy (SDL_Renderer *renderer);

void HandleResizeScreen();
void HandleResizeField();

void DrawGriddyField(SDL_Renderer *renderer);
void DrawGriddyFieldOfPlay (SDL_Renderer *renderer, SDL_Rect* Rect_Layout, SDL_Rect* Rect_FieldOfPlay);
void DrawGriddyYardLines(SDL_Renderer *renderer, SDL_Rect *Rect_FieldOfPlay);
void DrawGriddyEndzones (SDL_Renderer *renderer, SDL_Rect *Rect_FieldOfPlay);
void DrawGriddySidelines (SDL_Renderer *renderer, SDL_Rect *Rect_FieldOfPlay);
void DrawGriddyBenchArea (SDL_Renderer *renderer, SDL_Rect *Rect_FieldOfPlay);
void DrawGriddyBenchArea (SDL_Renderer *renderer, SDL_Rect *Rect_FieldOfPlay);
void DrawGriddyGoals(SDL_Renderer *renderer, SDL_Rect *Rect_FieldOfPlay, FieldDimension_Griddy *FieldDimension_Griddy_variableScale);
void DrawGriddyHashMarks(SDL_Renderer *renderer, SDL_Rect *Rect_FieldOfPlay, FieldDimension_Griddy *FieldDimension_Griddy_variableScale, float scale);


void DrawGriddyFieldNumbers(SDL_Renderer *renderer,SDL_Rect *Rect_FieldOfPlay, FieldDimension_Griddy *FieldDimension_Griddy_variableScale, float scale);

void CalcFieldLayout(SDL_Rect* Rect_Layout);
void ScaleGriddyFieldOfPlay (SDL_Rect *Rect_Layout, SDL_Rect* Rect_FieldOfPlay);
void SetVariableGriddyDimensionScale (SDL_Rect *Rect_Layout, FieldDimension_Griddy *FieldDimension_Griddy_variableScale, float scale);


