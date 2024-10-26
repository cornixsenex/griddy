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

typedef enum {
	FIELD_TYPE_GRIDDY,
	FIELD_TYPE_FOOTY,
	FIELD_TYPE_NONE
} FieldType;

typedef struct {
	FieldType FieldType;
	int total_layout_length;
	int total_layout_width;
} FieldDimension;

typedef struct {
	FieldDimension base;
	int field_length;
	int field_width;
	int endzone_length;
	int sideline_width;
	int bench_area_length; //25 to 25 lines that's 50 yards = 150 feet
	int bench_area_width;
	int perimeter_width;
	int hash_marks_width;
	int hash_marks_length;
	int goal_width;
	int goal_line_length;
	//int bench_area_length;
} FieldDimension_Griddy;

typedef struct {
	FieldDimension base;
	int field_width;
	int field_length;
	//etc
} FieldDimension_Footy;

extern FieldDimension_Griddy FieldDimension_Griddy_Default;


