#include "draw_field.h"
#include "global.h"
#include <SDL2/SDL.h>
#include <stdio.h>

FieldDimension_Griddy FieldDimension_Griddy_Default;

FieldDimension_Griddy FieldDimension_Griddy_Default = {
	.base = {
		.total_layout_length =  390,
		.total_layout_width = 250,
		.FieldType = FIELD_TYPE_GRIDDY,
	},
	.field_length = 300,
	.field_width = 160,
	.endzone_length = 30,
	.sideline_width = 6,
	.bench_area_length = 150,
	.bench_area_width = 30,
	.perimeter_width = 9,
	.hashSpaceWidth = 40,   // Width between the inner hashmark points (IE the width of the hash space)
	.hashMarkLength = 4,  // Length of the actual hashes (Width is 2 inches btw but I'm using lines for now)
	.goalWidth = 18.5, //Widthe of the goal is distance between two goalposts
	.goalDepth = 6.5, //length of the lines that represent the goalposts IE the depts of the goal (length between uprights and goal post)
};

int DrawScreen(SDL_Renderer *renderer) {

	int GameScreen = false;
	
	if (GameScreen != GAME_SCREEN_TEST) {
		printf ("GameScreen != GAME_SCREEN_TEST\n");
		return false;
	} else {
		DrawGriddyField(renderer);

		//DrawPlayers(renderer);

		//Last thing you do before return like actually draw it onto the screen
		RenderGriddy(renderer);
		return true;
	}
}

void RenderGriddy(SDL_Renderer *renderer)
{
	//Present the render
	SDL_RenderPresent(renderer);
}

void HandleResizeScreen() {
	griddySDL_Data.screenSizeRect.w = griddySDL_Data.pollEvent.window.data1;
	griddySDL_Data.screenSizeRect.h = griddySDL_Data.pollEvent.window.data2;
}

void DrawGriddyField(SDL_Renderer *renderer) 
{
	//Initialize the rectangles we will be drawing: layout, field of play, endzones, sidelines, bench area etc	
	SDL_Rect Rect_Layout, Rect_FieldOfPlay;
	float scale;

	FieldDimension_Griddy FieldDimension_Griddy_variableScale;

	//Draw Black background - Clear the entire window and make it black
	SDL_SetRenderDrawColor (renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);

	//Sets layout to scale with the window size
	CalcFieldLayout(&Rect_Layout);

	scale = Rect_Layout.w / FieldDimension_Griddy_Default.base.total_layout_length;

	SetVariableGriddyDimensionScale(&Rect_Layout, &FieldDimension_Griddy_variableScale, scale);

	//Draw Hot Pink total layout (which should all get covered up, right?)
	SDL_SetRenderDrawColor (renderer, 255, 0, 255, 255);
	SDL_RenderFillRect(renderer, &Rect_Layout);

	//Draw Green Field of Play
	DrawGriddyFieldOfPlay(renderer, &Rect_Layout, &Rect_FieldOfPlay);

	//Draw End zones
	DrawGriddyEndzones(renderer, &Rect_FieldOfPlay);
	
	//Draw Sidelines
	DrawGriddySidelines(renderer, &Rect_FieldOfPlay);

	//Draw Bench Area
	DrawGriddyBenchArea(renderer, &Rect_FieldOfPlay);

	//Draw Goals
	DrawGriddyGoals(renderer, &Rect_FieldOfPlay, &FieldDimension_Griddy_variableScale);

	//Draw Hash Marks
	DrawGriddyHashMarks(renderer, &Rect_FieldOfPlay, &FieldDimension_Griddy_variableScale, scale);
	//Draw Perimeter
	//Draw Numbers
	//Draw players ?
}

void ScaleGriddyFieldOfPlay (SDL_Rect *Rect_Layout, SDL_Rect* Rect_FieldOfPlay)
{
	//The length of the playing field (width of the FieldOfPlay_Rect) which is equal to layoutRect.w * .field_length   / .total_layout_length
	Rect_FieldOfPlay->w = Rect_Layout->w * FieldDimension_Griddy_Default.field_length / FieldDimension_Griddy_Default.base.total_layout_length;
	//The width of the playing field (height of the FieldOfPlay_Rect) which is equal to  layoutRect.h * .field_width / .total_layout_width 
	Rect_FieldOfPlay->h = Rect_Layout->h * FieldDimension_Griddy_Default.field_width / FieldDimension_Griddy_Default.base.total_layout_width;

	//Calculate the XY of the fieldOfPlay_Rect - Find the total difference between layout and fieldOfPlay then divide that in half to get the top left coordinates
	Rect_FieldOfPlay->x = Rect_Layout->x + ( (Rect_Layout->w - Rect_FieldOfPlay->w) / 2);
	Rect_FieldOfPlay->y = Rect_Layout->y + ( (Rect_Layout->h - Rect_FieldOfPlay->h) / 2);
}

void DrawGriddyFieldOfPlay (SDL_Renderer *renderer, SDL_Rect *Rect_Layout, SDL_Rect* Rect_FieldOfPlay)
{

	ScaleGriddyFieldOfPlay(Rect_Layout, Rect_FieldOfPlay);

	//The field should be green so that's the color we're going to draw
	SDL_SetRenderDrawColor (renderer, 80, 180, 100, 255);

	//Render the field of play	
	SDL_RenderFillRect(renderer, Rect_FieldOfPlay);

	//Draw the yard lines
	DrawGriddyYardLines(renderer, Rect_FieldOfPlay);
}

void DrawGriddyYardLines(SDL_Renderer *renderer, SDL_Rect *fieldOfPlay_Rect) 
{
	int i = 0; 
	
	//set White lines
	SDL_SetRenderDrawColor (renderer, 255, 255, 255, 255);
	
	//draw a line from a point x, y where x is the left end of the field plus i/20 of the field which is 1 / 20 or 5 units in a 100 unit wide field and y is the upper limit of the field to x, y where x is the same as above and y is the bottom limit of the field (y + h)

	//You need to draw 20 lines across the field

	for (i = 0; i < 21; i++) {
		SDL_RenderDrawLine(renderer, fieldOfPlay_Rect->x + (fieldOfPlay_Rect->w / 20 * i), fieldOfPlay_Rect->y, fieldOfPlay_Rect->x + (fieldOfPlay_Rect->w / 20 * i), fieldOfPlay_Rect->y + fieldOfPlay_Rect->h); 

	}	
}

void DrawGriddyEndzones (SDL_Renderer *renderer, SDL_Rect *Rect_FieldOfPlay)
{
	SDL_Rect Rect_EndzoneLeft, Rect_EndzoneRight;

	//End zone color - White for now but should be dependant on team
	SDL_SetRenderDrawColor (renderer, 255, 255, 255, 255);
	
	//First the left then the right
	
	//Left Endzone
	//The height is the same as the field of play
	Rect_EndzoneLeft.h = Rect_FieldOfPlay->h;
	//The length is 10 yards (proportional of course)
	Rect_EndzoneLeft.w = Rect_FieldOfPlay->w / 10;
	//the x is the fieldofplay - 10
	Rect_EndzoneLeft.x = Rect_FieldOfPlay->x - Rect_EndzoneLeft.w;
	//the y is fieldofplay
	Rect_EndzoneLeft.y = Rect_FieldOfPlay->y;

	//Right Endzone
	//The height is the same as the field of play
	Rect_EndzoneRight.h = Rect_FieldOfPlay->h;
	//The length is 10 yards (proportional of course)
	Rect_EndzoneRight.w = Rect_FieldOfPlay->w / 10;
	//the x is the fieldofplay + 10
	Rect_EndzoneRight.x = Rect_FieldOfPlay->x + Rect_FieldOfPlay->w;
	//the y is fieldofplay
	Rect_EndzoneRight.y = Rect_FieldOfPlay->y;

	//Draw the endzone rectangles
	SDL_RenderFillRect(renderer, &Rect_EndzoneLeft);
	SDL_RenderFillRect(renderer, &Rect_EndzoneRight);

}

void DrawGriddySidelines (SDL_Renderer *renderer, SDL_Rect *Rect_FieldOfPlay) 
{
	int endzoneWidth, sidelineWidth;
	SDL_Rect Rect_SidelineTop, Rect_SidelineLeft, Rect_SidelineBottom, Rect_SidelineRight;

	//Make sure the endzone and sidelines are proprotional to the field
	endzoneWidth = Rect_FieldOfPlay->w * FieldDimension_Griddy_Default.endzone_length / FieldDimension_Griddy_Default.field_length; 
	sidelineWidth = Rect_FieldOfPlay->w * FieldDimension_Griddy_Default.sideline_width / FieldDimension_Griddy_Default.field_length; 

	//Get dimensions for
	
	//SIDELINE TOP
	Rect_SidelineTop.x = Rect_FieldOfPlay->x - endzoneWidth;
	Rect_SidelineTop.y = Rect_FieldOfPlay->y - sidelineWidth;
	Rect_SidelineTop.w = Rect_FieldOfPlay->w + (2 * endzoneWidth);
	Rect_SidelineTop.h = sidelineWidth;

	//SIDELINE LEFT
	//x = Rect_FieldOfPlay.x - endzone width - sideline width
	Rect_SidelineLeft.x = Rect_FieldOfPlay->x - endzoneWidth - sidelineWidth;
	//y = Rect_FieldOfPlay.y - Sideline Width
	Rect_SidelineLeft.y = Rect_FieldOfPlay->y - sidelineWidth;
	//w = sideline width
	Rect_SidelineLeft.w = sidelineWidth;
	//h = 2 sideline width + field width 
	Rect_SidelineLeft.h = (2 * sidelineWidth) + Rect_FieldOfPlay->h;

	//SIDELINE BOTTOM
	//x = Rect_FieldOfPlay.x - endzone width
	Rect_SidelineBottom.x = Rect_FieldOfPlay->x - endzoneWidth;
	//y = Rect_FieldOfPlay.y + Sideline Width
	Rect_SidelineBottom.y = Rect_FieldOfPlay->y + Rect_FieldOfPlay->h;
	//w = FieldofPlay.w + 2 endzone width
	Rect_SidelineBottom.w = Rect_FieldOfPlay->w + (2 * endzoneWidth);
	//h = sideline width
	Rect_SidelineBottom.h = sidelineWidth;

	//SIDELINE RIGHT
	Rect_SidelineRight.x = Rect_FieldOfPlay->x +  Rect_FieldOfPlay->w + endzoneWidth;
	//y = Rect_FieldOfPlay.y - Sideline Width
	Rect_SidelineRight.y = Rect_FieldOfPlay->y - sidelineWidth;
	//w = sideline width
	Rect_SidelineRight.w = sidelineWidth;
	//h = 2 sideline width + field width 
	Rect_SidelineRight.h = (2 * sidelineWidth) + Rect_FieldOfPlay->h;
	

	//RENDER SIDELINES
	SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
	SDL_RenderFillRect(renderer, &Rect_SidelineTop);
	SDL_RenderFillRect(renderer, &Rect_SidelineLeft);
	SDL_RenderFillRect(renderer, &Rect_SidelineBottom);
	SDL_RenderFillRect(renderer, &Rect_SidelineRight);
	
}

void DrawGriddyBenchArea (SDL_Renderer *renderer, SDL_Rect *Rect_FieldOfPlay) 
{
	SDL_Rect Rect_BenchAreaTop, Rect_BenchAreaBottom;
	float fieldScale;

	fieldScale = Rect_FieldOfPlay->w / FieldDimension_Griddy_Default.field_length;
	printf("FIELD SCALE: %f\n", fieldScale);

	//Calculate dimensions of the two Bench Areas (Proportional to the field of course)
	Rect_BenchAreaTop.w = FieldDimension_Griddy_Default.bench_area_length * fieldScale;
	Rect_BenchAreaTop.h = FieldDimension_Griddy_Default.bench_area_width * fieldScale; 
	Rect_BenchAreaTop.x = Rect_FieldOfPlay->x + (FieldDimension_Griddy_Default.field_length - FieldDimension_Griddy_Default.bench_area_length) * fieldScale / 2;
	Rect_BenchAreaTop.y = Rect_FieldOfPlay->y - (FieldDimension_Griddy_Default.bench_area_width * fieldScale) - (FieldDimension_Griddy_Default.sideline_width * fieldScale);

	Rect_BenchAreaBottom.w = FieldDimension_Griddy_Default.bench_area_length * fieldScale;
	Rect_BenchAreaBottom.h = FieldDimension_Griddy_Default.bench_area_width * fieldScale; 
	Rect_BenchAreaBottom.x = Rect_FieldOfPlay->x + (FieldDimension_Griddy_Default.field_length - FieldDimension_Griddy_Default.bench_area_length) * fieldScale / 2;
	Rect_BenchAreaBottom.y = Rect_FieldOfPlay->y + Rect_FieldOfPlay->h + (FieldDimension_Griddy_Default.sideline_width * fieldScale);

	//Render the actual rectangles on the screen
	SDL_SetRenderDrawColor (renderer, 255, 0, 0, 255);

	SDL_RenderFillRect(renderer, &Rect_BenchAreaTop);
	SDL_RenderFillRect(renderer, &Rect_BenchAreaBottom);
}

void DrawGriddyGoals(SDL_Renderer *renderer, SDL_Rect *Rect_FieldOfPlay, FieldDimension_Griddy *FieldDimension_Griddy_variableScale) 
{
	int x1, x2, x3, x4, y1, y2;

	// Left goal
	// Top Line
	// Y1 and Y2 should be the same
	// goalDepth = X2 - X1
	x2 = Rect_FieldOfPlay->x - FieldDimension_Griddy_variableScale->endzone_length;
	x1 = x2 - FieldDimension_Griddy_variableScale->goalDepth;
	printf("X2: %d\n", x2);

	x3 = Rect_FieldOfPlay->x + Rect_FieldOfPlay->w + FieldDimension_Griddy_variableScale->endzone_length;
	x4 = x3 + FieldDimension_Griddy_variableScale->goalDepth;

	//To get Y you must find the midpoint of the field then either add or subtract HALF of the goal width
	
	//midpoint = Rect_FieldOfPlay->y + (Rect_FieldOfPlay->h / 2)
	y1 = Rect_FieldOfPlay->y + (Rect_FieldOfPlay->h / 2) - (FieldDimension_Griddy_variableScale->goalWidth / 2);
	y2 = Rect_FieldOfPlay->y + (Rect_FieldOfPlay->h / 2) + (FieldDimension_Griddy_variableScale->goalWidth / 2);

	//Set the color
	SDL_SetRenderDrawColor (renderer, 255, 215, 99, 255);

	//Draw lines
	
	//Top Left
	SDL_RenderDrawLine(renderer, x1, y1, x2, y1);
	//Bottom Left
	SDL_RenderDrawLine(renderer, x1, y2, x2, y2);
	//Top Right
	SDL_RenderDrawLine(renderer, x3, y1, x4, y1);
	//Bottom Right
	SDL_RenderDrawLine(renderer, x3, y2, x4, y2);
}

void CalcFieldLayout(SDL_Rect* Rect_Layout)
{
	float floatScreenWidth, floatLayoutLength;
	int intLayoutWidth, intFieldLength, intLayoutLength;
	floatScreenWidth = griddySDL_Data.screenSizeRect.w;
	floatLayoutLength = FieldDimension_Griddy_Default.base.total_layout_length;


	//First use the width and then check if the height is too much, in that case use the height instead, but then also double check if the length is too much then print an error I guess (because it tried to limit on x and y and fialed both idk how that's possible basically so yeah
	//
	//First determine which is the limiting factor then use it as the basis for the field size
	
	//If the ration of W/H is more than L/W then use Y as the limiting factor
	//NOTE: I used to maintain a margin, it's abandoned (commented out) now
	if ( floatScreenWidth / griddySDL_Data.screenSizeRect.h > floatLayoutLength / FieldDimension_Griddy_Default.base.total_layout_width) {
		//Y limiting factor
		printf("Y\n%d  :  %d\n%f\n", griddySDL_Data.screenSizeRect.w, griddySDL_Data.screenSizeRect.h, floatScreenWidth / griddySDL_Data.screenSizeRect.h);
		Rect_Layout->h = griddySDL_Data.screenSizeRect.h; // - (griddySDL_Data.screenSizeRect.h / 5);
		Rect_Layout->w = Rect_Layout->h * FieldDimension_Griddy_Default.base.total_layout_length / FieldDimension_Griddy_Default.base.total_layout_width;
	} else {
		//X limiting factor
		printf("X\n%d  :  %d\n%f\n", griddySDL_Data.screenSizeRect.w, griddySDL_Data.screenSizeRect.h, floatScreenWidth / griddySDL_Data.screenSizeRect.h);
		Rect_Layout->w = griddySDL_Data.screenSizeRect.w; // - (griddySDL_Data.screenSizeRect.w / 5);
		Rect_Layout->h  = Rect_Layout->w * FieldDimension_Griddy_Default.base.total_layout_width / FieldDimension_Griddy_Default.base.total_layout_length;
	}

	intLayoutWidth = Rect_Layout->w;
	intFieldLength = FieldDimension_Griddy_Default.field_length;
	intLayoutLength = FieldDimension_Griddy_Default.base.total_layout_length;

	//This just ensures actual field of play is a multiple of 20
//	while ( (Rect_Layout->w * FieldDimension_Griddy_Default.field_length / FieldDimension_Griddy_Default.base.total_layout_length) % 20 != 0) {
	while ( (intLayoutWidth * intFieldLength / intLayoutLength) % 20 != 0) {
		Rect_Layout->w -= 1;
		intLayoutWidth = Rect_Layout->w;
		intFieldLength = FieldDimension_Griddy_Default.field_length;
		intLayoutLength = FieldDimension_Griddy_Default.base.total_layout_length;
	}
	Rect_Layout->h  = Rect_Layout->w * FieldDimension_Griddy_Default.base.total_layout_width / FieldDimension_Griddy_Default.base.total_layout_length;

	//SET MARGINS - Total Margin is the difference between the screensize and the layout size / one side margin is half that	
	Rect_Layout->x = (griddySDL_Data.screenSizeRect.w - Rect_Layout->w) / 2;
	Rect_Layout->y = (griddySDL_Data.screenSizeRect.h - Rect_Layout->h) / 2;
}

void SetVariableGriddyDimensionScale (SDL_Rect *Rect_Layout, FieldDimension_Griddy *FieldDimension_Griddy_variableScale, float scale)
{

	//Define a porportional set of field data so I'm not just constantly doing scalar multiplication

	printf("SCALE: %f\n", scale);	

	//Create a scale multiplier so I'm not just doing calcs on each line

	FieldDimension_Griddy_variableScale->base.total_layout_length = scale * 390;
	FieldDimension_Griddy_variableScale->base.total_layout_width = scale * 250;
	FieldDimension_Griddy_variableScale->base.FieldType = scale * FIELD_TYPE_GRIDDY;
	FieldDimension_Griddy_variableScale->field_length = scale * 300;
	FieldDimension_Griddy_variableScale->field_width = scale * 160;
	FieldDimension_Griddy_variableScale->endzone_length = scale * 30;
	FieldDimension_Griddy_variableScale->sideline_width = scale * 6;
	FieldDimension_Griddy_variableScale->bench_area_length = scale * 150;
	FieldDimension_Griddy_variableScale->bench_area_width = scale * 30;
	FieldDimension_Griddy_variableScale->perimeter_width = scale * 9;
	FieldDimension_Griddy_variableScale->hashSpaceWidth = scale * FieldDimension_Griddy_Default.hashSpaceWidth; //Should be idk the width they take up on the field
	FieldDimension_Griddy_variableScale->hashMarkLength = scale * FieldDimension_Griddy_Default.hashMarkLength;// Should be the distance between the actual marks I guess or the length of the actual marks
	FieldDimension_Griddy_variableScale->goalWidth = scale * 18.5; //Widthe of the goal is distance between two goalposts
	FieldDimension_Griddy_variableScale->goalDepth = scale * 6.5; 
}

void DrawGriddyHashMarks(SDL_Renderer *renderer, SDL_Rect *Rect_FieldOfPlay, FieldDimension_Griddy *FieldDimension_Griddy_variableScale, float scale)
{

	//80 total marks. Every single yard excluding the 20 multiple of 5 yards with goal lines (counting 100 but not 0 because [i]ndex)
	//each line pair has the same x
	//all top lines share the same y
	//all bottom lines share the same y
	//all lines will be the same width
	//
	//
	//
	//
	int i;
	float y1, y2, y3, y4, midpoint, x;

	midpoint = Rect_FieldOfPlay->y + (FieldDimension_Griddy_variableScale->field_width / 2);

	y1 = midpoint - (FieldDimension_Griddy_variableScale->hashSpaceWidth / 2);
	y2 = midpoint - (FieldDimension_Griddy_variableScale->hashSpaceWidth / 2) - FieldDimension_Griddy_variableScale->hashMarkLength;
	
	y3 = midpoint + (FieldDimension_Griddy_variableScale->hashSpaceWidth / 2);
	y4 = midpoint + (FieldDimension_Griddy_variableScale->hashSpaceWidth / 2) + FieldDimension_Griddy_variableScale->hashMarkLength;

	//Set color - White
	SDL_SetRenderDrawColor (renderer, 255, 255, 255, 255);

	for (i = 0; i < 100; i++) {
	   if (i % 5 != 0) {
		   x = Rect_FieldOfPlay->x + (Rect_FieldOfPlay->w * i / 100);

		   SDL_RenderDrawLine(renderer, x, y1, x, y2);
		   SDL_RenderDrawLine(renderer, x, y3, x, y4);
	   }
	}
}


