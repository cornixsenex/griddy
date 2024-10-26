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
	.hash_marks_width = 0, //Should be idk the width they take up on the field
	.hash_marks_length = 0,// Should be the distance between the actual marks I guess or the length of the actual marks
	.goal_width = 0, //Widthe of the goal is distance between two goalposts
.goal_line_length = 0, //length of the lines that represent the goalposts
};


void DrawGriddyField(SDL_Renderer *renderer) 
{
	//Initialize the rectanges we will be drawing: layout, field of play, endzones, sidelines, bench area etc	
	SDL_Rect Rect_Layout, Rect_FieldOfPlay;

	//Draw Black background - Clear the entire window and make it black
	SDL_SetRenderDrawColor (renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);

	//Sets layout to scale with the window size
	CalcFieldLayout(&Rect_Layout);

	//Draw Hot Pink total layout (which should all get covered up, right?)
	SDL_SetRenderDrawColor (renderer, 255, 0, 255, 255);
	SDL_RenderFillRect(renderer, &Rect_Layout);
	//Draw Green Field of Play
	DrawGriddyFieldOfPlay(renderer, &Rect_Layout, &Rect_FieldOfPlay);

	//Draw End zones
	DrawGriddyEndzones(renderer, &Rect_FieldOfPlay);
	
	//Draw Sidelines
	DrawGriddySidelines(renderer, &Rect_FieldOfPlay);

	//Draw Goals
	//Draw Hash Marks
	//Draw Bench Area
	//Draw Perimeter
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
	//First draw a white box around the field - far left endzone / 0 yard line is the i=0 goalline btw
//	SDL_RenderDrawLine(renderer, griddySDLData.fieldRect.x, griddySDLData.fieldRect.y, griddySDLData.fieldRect.x + griddySDLData.fieldRect.w, griddySDLData.fieldRect.y);
//	SDL_RenderDrawLine(renderer, griddySDLData.fieldRect.x + griddySDLData.fieldRect.w, griddySDLData.fieldRect.y, griddySDLData.fieldRect.x + griddySDLData.fieldRect.w, griddySDLData.fieldRect.y + griddySDLData.fieldRect.h);
//	SDL_RenderDrawLine(renderer, griddySDLData.fieldRect.x, griddySDLData.fieldRect.y + griddySDLData.fieldRect.h,  griddySDLData.fieldRect.x + griddySDLData.fieldRect.w, griddySDLData.fieldRect.y + griddySDLData.fieldRect.h);

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
		SDL_RenderDrawLine(renderer, fieldOfPlay_Rect->x + (fieldOfPlay_Rect->w / 20 * i), fieldOfPlay_Rect->y, fieldOfPlay_Rect->x + (fieldOfPlay_Rect->w / 20 * i), fieldOfPlay_Rect->y + fieldOfPlay_Rect->h); 
		//draw a line from a point x, y where x is the left end of the field plus i/20 of the field which is 1 / 20 or 5 units in a 100 unit wide field and y is the upper limit of the field to x, y where x is the same as above and y is the bottom limit of the field (y + h)
		//SDL_RenderDrawLine(renderer, griddySDLData.fieldRect.x + ((griddySDLData.fieldRect.w / 20) * i), griddySDLData.fieldRect.y, griddySDLData.fieldRect.x + ((griddySDLData.fieldRect.w / 20) * i), griddySDLData.fieldRect.y + griddySDLData.fieldRect.h);
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
//	int x, y, w, h, x1, y1, x2, y2, goalWidth;
//	//this is the total width of the field
////	x = griddySDLData.fieldRect.x;
////	//upper limit is y value of the fieldRect as defined
////	y = griddySDLData.fieldRect.y;
////	//this is just the x value where the top left corner of the field is
////	w = griddySDLData.fieldRect.w;
////	//This is the total height (which goes down btw) of the field	
////	h = griddySDLData.fieldRect.h; 
//	//goalWidth is the length of the lines which draw the goalpost limits (it's width on this 2d field but it's 'depth' in the 3d field)
//	//goalWidth = w / 20;
//
//	//Goals are at the end of the endzone which is not currently inside fieldRect (maybe fix this right idk)
//
//	//Goals are yellow
//	SDL_SetRenderDrawColor (renderer, 255, 215, 0, 255);
//
//	//Draw Left Goals
//	
//	//Draw top left goal line (horizontal line that forms the north limit of the left goal)
//	x1 = x - goalWidth;
//	y1 = y +  (3.5 * h / 8);
//	x2 = x + goalWidth;
//	SDL_RenderDrawLine(renderer, x1, y1, x2, y1);
//
//	//Draw bottom left goal line
//	y2 = y + (4.5 * h / 8);
//	SDL_RenderDrawLine(renderer, x1, y2, x2, y2);
//	
//	//Draw Right Goals
//	x1 = x + w - goalWidth;
//	x2 = x + w + goalWidth;
//	SDL_RenderDrawLine(renderer, x1, y1, x2, y1);
//	SDL_RenderDrawLine(renderer, x1, y2, x2, y2);
}

void RenderGriddy(SDL_Renderer *renderer)
{
	//Present the render
	SDL_RenderPresent(renderer);
}

void HandleResizeScreen() {
	griddySDL_Data.screenSizeRect.w = griddySDL_Data.pollEvent.window.data1;
	griddySDL_Data.screenSizeRect.h = griddySDL_Data.pollEvent.window.data2;

//	HandleResizeField();
	//printf("Window resized to %dx%d\n", griddySDLData.pollEvent.window.data1, griddySDLData.pollEvent.window.data2);
}

void CalcFieldLayout(SDL_Rect* Rect_Layout)
{
	//First use the width and then check if the height is too much, in that case use the height instead, but then also double check if the length is too much then print an error I guess (because it tried to limit on x and y and fialed both idk how that's possible basically so yeah
	//
	//First determine which is the limiting factor then use it as the basis for the field size
	

	//If the ration of W/H is less than L/W then use Y as the limiting factor
	if ( griddySDL_Data.screenSizeRect.w / griddySDL_Data.screenSizeRect.h > FieldDimension_Griddy_Default.base.total_layout_length / FieldDimension_Griddy_Default.base.total_layout_width) {
		printf("Y limiting factor\n");
		Rect_Layout->h = griddySDL_Data.screenSizeRect.h - (griddySDL_Data.screenSizeRect.h / 5);
		Rect_Layout->w = Rect_Layout->h * FieldDimension_Griddy_Default.base.total_layout_length / FieldDimension_Griddy_Default.base.total_layout_width;
	} else {
		printf("X limiting factor\n");
		Rect_Layout->w = griddySDL_Data.screenSizeRect.w - (griddySDL_Data.screenSizeRect.w / 5);
		Rect_Layout->h  = Rect_Layout->w * FieldDimension_Griddy_Default.base.total_layout_width / FieldDimension_Griddy_Default.base.total_layout_length;
	}

	//This just ensures actual field of play is a multiple of 20
	while ( (Rect_Layout->w * FieldDimension_Griddy_Default.field_length / FieldDimension_Griddy_Default.base.total_layout_length) % 20 != 0) {
		Rect_Layout->w -= 1;
	}
	Rect_Layout->h  = Rect_Layout->w * FieldDimension_Griddy_Default.base.total_layout_width / FieldDimension_Griddy_Default.base.total_layout_length;


	//SET MARGINS - Total Margin is the difference between the screensize and the layout size / one side margin is half that	
	Rect_Layout->x = (griddySDL_Data.screenSizeRect.w - Rect_Layout->w) / 2;
	Rect_Layout->y = (griddySDL_Data.screenSizeRect.h - Rect_Layout->h) / 2;
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
	SDL_Rect Rect_SidelineTop;//, Rect_SidelineLeft, Rect_SidelineBottom, Rect_SidelineRight;

	//Make sure the endzone and sidelines are proprotional to the field
	endzoneWidth = Rect_FieldOfPlay->w * FieldDimension_Griddy_Default.endzone_length / FieldDimension_Griddy_Default.field_length; 
	sidelineWidth = Rect_FieldOfPlay->w * FieldDimension_Griddy_Default.sideline_width / FieldDimension_Griddy_Default.field_length; 

	//Get dimensions for
	
	//SIDELINE TOP
	//x = Rect_FieldOfPlay.x - endzone width 
	Rect_SidelineTop.x = Rect_FieldOfPlay->x - endzoneWidth;
	//y = Rect_FieldOfPlay.y - Sideline Width
	Rect_SidelineTop.y = Rect_FieldOfPlay->y - sidelineWidth;
	//w = FieldofPlay.w + 2 endzone width
	Rect_SidelineTop.w = Rect_FieldOfPlay->w + (2 * endzoneWidth);
	//h = sideline width
	Rect_SidelineTop.h = sidelineWidth;

	//SIDELINE LEFT
	//x = Rect_FieldOfPlay.x - endzone width - sideline width
	//y = Rect_FieldOfPlay.y - Sideline Width
	//w = sideline width
	//h = 2 sideline width + field width 

	//SIDELINE BOTTOM
	//x = Rect_FieldOfPlay.x - endzone width
	//y = Rect_FieldOfPlay.y + Sideline Width
	//w = FieldofPlay.w + 2 endzone width
	//h = sideline width

	//SIDELINE RIGHT
	//x = Rect_FieldOfPlay.x +  Rect_FieldOfPlay.w + endzone width
	//y = Rect_FieldOfPlay.y - Sideline Width
	//w = sideline width
	//h = 2 sideline width + field width 
	

	//RENDER SIDELINES
	SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
	SDL_RenderFillRect(renderer, &Rect_SidelineTop);
	//SDL_RenderFillRect(renderer, &Rect_SidelineLeft);
	//SDL_RenderFillRect(renderer, &Rect_SidelineBottom);
	//SDL_RenderFillRect(renderer, &Rect_SidelineRight);
	


}
	
