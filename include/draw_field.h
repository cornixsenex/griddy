#include <SDL2/SDL.h>

void DrawGriddyField(SDL_Renderer *renderer);
void RenderGriddy (SDL_Renderer *renderer);
void DrawGriddyFieldGoals(SDL_Renderer *renderer);
void HandleResizeScreen();
void HandleResizeField();
int DrawScreen(SDL_Renderer *renderer); 
void DrawGriddyFieldLines(SDL_Renderer *renderer);

typedef enum {
	FIELD_TYPE_GRIDDY,
	FIELD_TYPE_FOOTY,
	FIELD_TYPE_NONE
} FieldType;

typedef struct {
	FieldType FieldType;
	int total_length;
	int total_width;
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


