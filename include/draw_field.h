#include <SDL2/SDL.h>

void DrawGriddyField(SDL_Renderer *renderer);
void DrawGriddyFieldOfPlay (SDL_Renderer *renderer, SDL_Rect* Rect_Layout, SDL_Rect* Rect_FieldOfPlay);
void DrawGriddyYardLines(SDL_Renderer *renderer, SDL_Rect *Rect_FieldOfPlay);
void RenderGriddy (SDL_Renderer *renderer);
void DrawGriddyFieldGoals(SDL_Renderer *renderer);
void HandleResizeScreen();
void HandleResizeField();
int DrawScreen(SDL_Renderer *renderer); 
void CalcFieldLayout(SDL_Rect* Rect_Layout);
void ScaleGriddyFieldOfPlay (SDL_Rect *Rect_Layout, SDL_Rect* Rect_FieldOfPlay);
void DrawGriddyEndzones (SDL_Renderer *renderer, SDL_Rect *Rect_FieldOfPlay);
void DrawGriddySidelines (SDL_Renderer *renderer, SDL_Rect *Rect_FieldOfPlay);
void DrawGriddyBenchArea (SDL_Renderer *renderer, SDL_Rect *Rect_FieldOfPlay);
void DrawGriddyGoals(SDL_Renderer *renderer, SDL_Rect *Rect_FieldOfPlay);

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
	float field_length;
	float field_width;
	float endzone_length;
	float sideline_width;
	float bench_area_length; //25 to 25 lines that's 50 yards = 150 feet
	float bench_area_width;
	float perimeter_width;
	float hash_marks_width;
	float hash_marks_length;
	float goal_width;
	float goal_line_length;
	//int bench_area_length;
} FieldDimension_Griddy;

typedef struct {
	FieldDimension base;
	float field_width;
	float field_length;
	//etc
} FieldDimension_Footy;

extern FieldDimension_Griddy FieldDimension_Griddy_Default;


