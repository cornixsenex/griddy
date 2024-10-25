#include "draw_field.h"
#include "global.h"
#include <SDL2/SDL.h>

FieldDimension_Griddy FieldDimension_Griddy_Default;

FieldDimension_Griddy FieldDimension_Griddy_Default = {
	.base = {
		.total_length =  390,
		.total_width = 250,
		.FieldType = FIELD_TYPE_GRIDDY,
	},
	.field_length = 300,
	.field_width = 160,
	.endzone_length = 30,
	.sideline_width = 6,
	.bench_area_length = 150,
	.bench_area_width = 30,
	.perimeter_width = 9,
	.hash_marks_width = 0, //Should be idk the width they take up on the field
	.hash_marks_length = 0,// Should be the distance between the actual marks I guess or the length of the actual marks
	.goal_width = 0, //Widthe of the goal is distance between two goalposts
	.goal_line_length = 0, //length of the lines that represent the goalposts
};


void DrawGriddyField(SDL_Renderer *renderer) 
{	
	//int x, y, w, h;
	//SDL_Rect endZone1_Rect, endZone2_Rect;
	//x = griddySDLData.fieldRect.x;
	//y = griddySDLData.fieldRect.y;
	//w = griddySDLData.fieldRect.w;
	//h = griddySDLData.fieldRect.h;
	//endZone1_Rect.x = x - (w/10); 
	//endZone1_Rect.y = y;
	//endZone1_Rect.w = w / 10;
	//endZone1_Rect.h = h;

	//endZone2_Rect.x = x + w; 
	//endZone2_Rect.y = y;
	//endZone2_Rect.w = w / 10;
	//endZone2_Rect.h = h;
	
	//Draw the entire Field Area (IE the relevant portion of the actual window size)
	//First clear the screen, then draw the total_length and total_width of the field

	//Draw Black background
	SDL_SetRenderDrawColor (renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);
	//Draw Green Field 	
	SDL_SetRenderDrawColor (renderer, 80, 180, 100, 255);
	SDL_RenderFillRect(renderer, &griddySDLData.fieldRect);
	//Draw End zones
	//SDL_SetRenderDrawColor (renderer, 255, 255, 255, 255);
	////Left end zone
	//SDL_RenderFillRect(renderer, &endZone1_Rect);
	////Right end zone
	//SDL_RenderFillRect(renderer, &endZone2_Rect);
	//Draw Goals
//	DrawFieldGoals(renderer);
	//Draw Hash Marks
	//Draw Goalines
	DrawGriddyFieldLines(renderer);
}

void DrawGriddyFieldLines(SDL_Renderer *renderer) 
{
	int i = 0; 
	
	//set White lines
	SDL_SetRenderDrawColor (renderer, 255, 255, 255, 255);
	//First draw a white box around the field - far left endzone / 0 yard line is the i=0 goalline btw
	SDL_RenderDrawLine(renderer, griddySDLData.fieldRect.x, griddySDLData.fieldRect.y, griddySDLData.fieldRect.x + griddySDLData.fieldRect.w, griddySDLData.fieldRect.y);
	SDL_RenderDrawLine(renderer, griddySDLData.fieldRect.x + griddySDLData.fieldRect.w, griddySDLData.fieldRect.y, griddySDLData.fieldRect.x + griddySDLData.fieldRect.w, griddySDLData.fieldRect.y + griddySDLData.fieldRect.h);
	SDL_RenderDrawLine(renderer, griddySDLData.fieldRect.x, griddySDLData.fieldRect.y + griddySDLData.fieldRect.h,  griddySDLData.fieldRect.x + griddySDLData.fieldRect.w, griddySDLData.fieldRect.y + griddySDLData.fieldRect.h);

	//upper limit is y value of the fieldRect as defined
//	y = griddySDLData.fieldRect.y;
//	//this is just the x value where the top left corner of the field is
//	fieldRectx = griddySDLData.fieldRect.x;
//	//this is the total width of the field
//	w = griddySDLData.fieldRect.w;
//	//This is the total height (which goes down btw) of the field	
//	h = griddySDLData.fieldRect.h; 
//

	//You need to draw 20 lines across the field
	for (i = 0; i < 21; i++) {
		//draw a line from a point x, y where x is the left end of the field plus i/20 of the field which is 1 / 20 or 5 units in a 100 unit wide field and y is the upper limit of the field to x, y where x is the same as above and y is the bottom limit of the field (y + h)
		SDL_RenderDrawLine(renderer, griddySDLData.fieldRect.x + ((griddySDLData.fieldRect.w / 20) * i), griddySDLData.fieldRect.y, griddySDLData.fieldRect.x + ((griddySDLData.fieldRect.w / 20) * i), griddySDLData.fieldRect.y + griddySDLData.fieldRect.h);
	}	
}

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

void DrawFieldGoals(SDL_Renderer *renderer)
{
	int x, y, w, h, x1, y1, x2, y2, goalWidth;
	//this is the total width of the field
	x = griddySDLData.fieldRect.x;
	//upper limit is y value of the fieldRect as defined
	y = griddySDLData.fieldRect.y;
	//this is just the x value where the top left corner of the field is
	w = griddySDLData.fieldRect.w;
	//This is the total height (which goes down btw) of the field	
	h = griddySDLData.fieldRect.h; 
	//goalWidth is the length of the lines which draw the goalpost limits (it's width on this 2d field but it's 'depth' in the 3d field)
	goalWidth = w / 20;

	//Goals are at the end of the endzone which is not currently inside fieldRect (maybe fix this right idk)

	//Goals are yellow
	SDL_SetRenderDrawColor (renderer, 255, 215, 0, 255);

	//Draw Left Goals
	
	//Draw top left goal line (horizontal line that forms the north limit of the left goal)
	x1 = x - goalWidth;
	y1 = y +  (3.5 * h / 8);
	x2 = x + goalWidth;
	SDL_RenderDrawLine(renderer, x1, y1, x2, y1);

	//Draw bottom left goal line
	y2 = y + (4.5 * h / 8);
	SDL_RenderDrawLine(renderer, x1, y2, x2, y2);
	
	//Draw Right Goals
	x1 = x + w - goalWidth;
	x2 = x + w + goalWidth;
	SDL_RenderDrawLine(renderer, x1, y1, x2, y1);
	SDL_RenderDrawLine(renderer, x1, y2, x2, y2);
}

void RenderGriddy(SDL_Renderer *renderer)
{
	//Present the render
	SDL_RenderPresent(renderer);
}

void HandleResizeScreen() {
	griddySDLData.screenSizeRect.w = griddySDLData.pollEvent.window.data1;
	griddySDLData.screenSizeRect.h = griddySDLData.pollEvent.window.data2;

	HandleResizeField();
	//printf("Window resized to %dx%d\n", griddySDLData.pollEvent.window.data1, griddySDLData.pollEvent.window.data2);
}

void HandleResizeField()
{

	//Always 10 % margin in all directions please. 
	griddySDLData.fieldRect.x = griddySDLData.screenSizeRect.w / 10;
	griddySDLData.fieldRect.y = griddySDLData.screenSizeRect.h / 10;
	griddySDLData.fieldRect.w = (griddySDLData.screenSizeRect.w / 10) * 8;
	//Make sure the field size is a multiple of 20 so that the grid lines are drawn correctly
	while (griddySDLData.fieldRect.w % 20 != 0) {
		griddySDLData.fieldRect.w -= 1;
	}
	griddySDLData.fieldRect.h = griddySDLData.fieldRect.w * 16 / 30;
}
