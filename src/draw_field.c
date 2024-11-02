#include "camera.h"
#include "draw_field.h"
#include "global.h"
#include "load_field_textures.h"
#include <SDL2/SDL.h>
#include <stdio.h>

FieldDimension_Griddy FieldDimension_Griddy_Default;

FieldDimension_Griddy FieldDimension_Griddy_Default = {
	.base = {
		.total_layout_length =  390,
		.total_layout_width = 250,
		.FieldType = FIELD_TYPE_GRIDDY,
	},
	.fieldLength = 300,
	.fieldWidth = 160,
	.endzone_length = 30,
	.sideline_width = 6,
	.bench_area_length = 150,
	.bench_area_width = 30,
	.perimeter_width = 9,
	.hashSpaceWidth = 40,   // Width between the inner hashmark points (IE the width of the hash space)
	.hashMarkLength = 4,  // Length of the actual hashes (Width is 2 inches btw but I'm using lines for now)
	.goalWidth = 18.5, //Widthe of the goal is distance between two goalposts
	.goalDepth = 6.5, //length of the lines that represent the goalposts IE the depts of the goal (length between uprights and goal post)

	.numberHeight = 6,
	.numberWidth = 4,
	.numberMargin = 21, //The space between the number and the sideline (tops of number 9 yards, number 2 yards tall, bottom of number to sideline is 7 yards = 21 feet
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
	//Update Window Size
	griddySDL_Data.screenSizeRect.w = griddySDL_Data.pollEvent.window.data1;
	griddySDL_Data.screenSizeRect.h = griddySDL_Data.pollEvent.window.data2;

	UpdateCameraObjectSize();
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
	
	//Draw Numbers
	DrawGriddyFieldNumbers(renderer, &Rect_FieldOfPlay, &FieldDimension_Griddy_variableScale);

	//TEST Draw partial texture (negative X value)
	TestDrawTexture(renderer);
	//Draw players ?
}

void ScaleGriddyFieldOfPlay (SDL_Rect *Rect_Layout, SDL_Rect* Rect_FieldOfPlay)
{
	//The length of the playing field (width of the FieldOfPlay_Rect) which is equal to layoutRect.w * .fieldLength   / .total_layout_length
	Rect_FieldOfPlay->w = Rect_Layout->w * FieldDimension_Griddy_Default.fieldLength / FieldDimension_Griddy_Default.base.total_layout_length;
	//The width of the playing field (height of the FieldOfPlay_Rect) which is equal to  layoutRect.h * .fieldWidth / .total_layout_width 
	Rect_FieldOfPlay->h = Rect_Layout->h * FieldDimension_Griddy_Default.fieldWidth / FieldDimension_Griddy_Default.base.total_layout_width;

	//Calculate the XY of the fieldOfPlay_Rect - Find the total difference between layout and fieldOfPlay then divide that in half to get the top left coordinates
	Rect_FieldOfPlay->x = Rect_Layout->x + ( (Rect_Layout->w - Rect_FieldOfPlay->w) / 2);
	Rect_FieldOfPlay->y = Rect_Layout->y + ( (Rect_Layout->h - Rect_FieldOfPlay->h) / 2);

	//Handle Camera Scale - Not coded yet
	//Rect_FieldOfPlay->x -= 150;
	//Rect_FieldOfPlay->y -= 150;
	//Rect_FieldOfPlay->w = Rect_FieldOfPlay->w * 2;
	//Rect_FieldOfPlay->h = Rect_FieldOfPlay->h * 2;

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
	endzoneWidth = Rect_FieldOfPlay->w * FieldDimension_Griddy_Default.endzone_length / FieldDimension_Griddy_Default.fieldLength; 
	sidelineWidth = Rect_FieldOfPlay->w * FieldDimension_Griddy_Default.sideline_width / FieldDimension_Griddy_Default.fieldLength; 

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

	fieldScale = Rect_FieldOfPlay->w / FieldDimension_Griddy_Default.fieldLength;

	//Calculate dimensions of the two Bench Areas (Proportional to the field of course)
	Rect_BenchAreaTop.w = FieldDimension_Griddy_Default.bench_area_length * fieldScale;
	Rect_BenchAreaTop.h = FieldDimension_Griddy_Default.bench_area_width * fieldScale; 
	Rect_BenchAreaTop.x = Rect_FieldOfPlay->x + (FieldDimension_Griddy_Default.fieldLength - FieldDimension_Griddy_Default.bench_area_length) * fieldScale / 2;
	Rect_BenchAreaTop.y = Rect_FieldOfPlay->y - (FieldDimension_Griddy_Default.bench_area_width * fieldScale) - (FieldDimension_Griddy_Default.sideline_width * fieldScale);

	Rect_BenchAreaBottom.w = FieldDimension_Griddy_Default.bench_area_length * fieldScale;
	Rect_BenchAreaBottom.h = FieldDimension_Griddy_Default.bench_area_width * fieldScale; 
	Rect_BenchAreaBottom.x = Rect_FieldOfPlay->x + (FieldDimension_Griddy_Default.fieldLength - FieldDimension_Griddy_Default.bench_area_length) * fieldScale / 2;
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
		Rect_Layout->h = griddySDL_Data.screenSizeRect.h; // - (griddySDL_Data.screenSizeRect.h / 5);
		Rect_Layout->w = Rect_Layout->h * FieldDimension_Griddy_Default.base.total_layout_length / FieldDimension_Griddy_Default.base.total_layout_width;
	} else {
		//X limiting factor
		Rect_Layout->w = griddySDL_Data.screenSizeRect.w; // - (griddySDL_Data.screenSizeRect.w / 5);
		Rect_Layout->h  = Rect_Layout->w * FieldDimension_Griddy_Default.base.total_layout_width / FieldDimension_Griddy_Default.base.total_layout_length;
	}

	intLayoutWidth = Rect_Layout->w;
	intFieldLength = FieldDimension_Griddy_Default.fieldLength;
	intLayoutLength = FieldDimension_Griddy_Default.base.total_layout_length;

	//This just ensures actual field of play is a multiple of 20
//	while ( (Rect_Layout->w * FieldDimension_Griddy_Default.fieldLength / FieldDimension_Griddy_Default.base.total_layout_length) % 20 != 0) {
	while ( (intLayoutWidth * intFieldLength / intLayoutLength) % 20 != 0) {
		Rect_Layout->w -= 1;
		intLayoutWidth = Rect_Layout->w;
		intFieldLength = FieldDimension_Griddy_Default.fieldLength;
		intLayoutLength = FieldDimension_Griddy_Default.base.total_layout_length;
	}
	Rect_Layout->h  = Rect_Layout->w * FieldDimension_Griddy_Default.base.total_layout_width / FieldDimension_Griddy_Default.base.total_layout_length;

	//SET MARGINS - Total Margin is the difference between the screensize and the layout size / one side margin is half that	
	Rect_Layout->x = (griddySDL_Data.screenSizeRect.w - Rect_Layout->w) / 2;
	Rect_Layout->y = (griddySDL_Data.screenSizeRect.h - Rect_Layout->h) / 2;

	//Accomodate Camera Translation and Zoom 
	//Rect_Layout->x -= griddyCameraObject.x;
	//Rect_Layout->y -= griddyCameraObject.y;
	//Rect_Layout->w *= griddyCameraObject.scale;
	//Rect_Layout->h *= griddyCameraObject.scale;
}

void SetVariableGriddyDimensionScale (SDL_Rect *Rect_Layout, FieldDimension_Griddy *FieldDimension_Griddy_variableScale, float scale)
{

	//Define a porportional set of field data so I'm not just constantly doing scalar multiplication

	FieldDimension_Griddy_variableScale->base.total_layout_length = scale * 390;
	FieldDimension_Griddy_variableScale->base.total_layout_width = scale * 250;
	FieldDimension_Griddy_variableScale->base.FieldType = scale * FIELD_TYPE_GRIDDY;
	FieldDimension_Griddy_variableScale->fieldLength = scale * 300;
	FieldDimension_Griddy_variableScale->fieldWidth = scale * 160;
	FieldDimension_Griddy_variableScale->endzone_length = scale * 30;
	FieldDimension_Griddy_variableScale->sideline_width = scale * 6;
	FieldDimension_Griddy_variableScale->bench_area_length = scale * 150;
	FieldDimension_Griddy_variableScale->bench_area_width = scale * 30;
	FieldDimension_Griddy_variableScale->perimeter_width = scale * 9;
	FieldDimension_Griddy_variableScale->hashSpaceWidth = scale * FieldDimension_Griddy_Default.hashSpaceWidth; //Should be idk the width they take up on the field
	FieldDimension_Griddy_variableScale->hashMarkLength = scale * FieldDimension_Griddy_Default.hashMarkLength;// Should be the distance between the actual marks I guess or the length of the actual marks
	FieldDimension_Griddy_variableScale->goalWidth = scale * 18.5; //Widthe of the goal is distance between two goalposts
	FieldDimension_Griddy_variableScale->goalDepth = scale * 6.5; 
	
	FieldDimension_Griddy_variableScale->numberHeight = scale * FieldDimension_Griddy_Default.numberHeight; 
	FieldDimension_Griddy_variableScale->numberWidth = scale * FieldDimension_Griddy_Default.numberWidth; 
	FieldDimension_Griddy_variableScale->numberMargin = scale * FieldDimension_Griddy_Default.numberMargin; 

}

void DrawGriddyHashMarks(SDL_Renderer *renderer, SDL_Rect *Rect_FieldOfPlay, FieldDimension_Griddy *FieldDimension_Griddy_variableScale, float scale)
{
	int i;
	float y1, y2, y3, y4, midpoint, x;

	midpoint = Rect_FieldOfPlay->y + (FieldDimension_Griddy_variableScale->fieldWidth / 2);

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

void DrawGriddyFieldNumbers(SDL_Renderer *renderer,SDL_Rect *Rect_FieldOfPlay, FieldDimension_Griddy *FieldDimension_Griddy_variableScale)
{
	//Declare the SDL_Rect onto which we will render the textures
	SDL_Rect Rect_FieldNumDest;

	//It's 5 seperate functions
	//Each prints sets of numbers on the appropriate locations of the proportional gridirion
	//10 20 30 and 40 are all 4 sets with sets on both sides of the field
	//50 is just the one set
	//while loop * 10 proportional yards * i
	//switch i to print certain number

	//All numbers will have the same dimensions wh no need to re-set only calculate their xy and render
	//W and H are defined in the FieldDimension
	Rect_FieldNumDest.w= FieldDimension_Griddy_variableScale->numberWidth;
	Rect_FieldNumDest.h= FieldDimension_Griddy_variableScale->numberHeight;

	//Draw the numbers subfunction
	DrawGriddyFieldNumbers10_40(renderer, Rect_FieldOfPlay, FieldDimension_Griddy_variableScale, &Rect_FieldNumDest, 1);
	DrawGriddyFieldNumbers10_40(renderer, Rect_FieldOfPlay, FieldDimension_Griddy_variableScale, &Rect_FieldNumDest, 2);
	DrawGriddyFieldNumbers10_40(renderer, Rect_FieldOfPlay, FieldDimension_Griddy_variableScale, &Rect_FieldNumDest, 3);
	DrawGriddyFieldNumbers10_40(renderer, Rect_FieldOfPlay, FieldDimension_Griddy_variableScale, &Rect_FieldNumDest, 4);

	DrawGriddyFieldNumbers50(renderer, Rect_FieldOfPlay, FieldDimension_Griddy_variableScale, &Rect_FieldNumDest);

	//DrawGriddyFieldNumbers50(renderer, Rect_FieldOfPlay, FieldDimension_Griddy_variableScale, &Rect_FieldNumDest);

}

void DrawGriddyFieldNumbers10_40(SDL_Renderer *renderer, SDL_Rect *Rect_FieldOfPlay, FieldDimension_Griddy *FieldDimension_Griddy_variableScale, SDL_Rect *Rect_FieldNumDest, int xYards)
{
	int numMargin = 3;	//3 foot margin between end of letter and goal line / irl it's like 6 inches but doesn't look good BUT adjustable for sure

	//Bottom Row
	//Y is just go down to field h and then subtract margin then subtrack num height
	Rect_FieldNumDest->y = Rect_FieldOfPlay->y + FieldDimension_Griddy_variableScale->fieldWidth - FieldDimension_Griddy_variableScale->numberMargin - FieldDimension_Griddy_variableScale->numberHeight;
	
	//Draw Bottom left set
	//First Draw the left, variable number	
	Rect_FieldNumDest->x = Rect_FieldOfPlay->x + (xYards * FieldDimension_Griddy_variableScale->fieldLength / 10) - numMargin - FieldDimension_Griddy_variableScale->numberWidth;

	//Render the texuture - note this is the variable number, texture is indexed to the textures array defined in load_field_texture
	SDL_RenderCopyEx(renderer, textures[xYards], NULL, Rect_FieldNumDest, 0, NULL, SDL_FLIP_NONE);

	//Next Draw the right 0
	//Num now on the right side of the goal line	
	Rect_FieldNumDest->x = Rect_FieldOfPlay->x + (xYards * FieldDimension_Griddy_variableScale->fieldLength / 10) + numMargin * 2;

	//Render the texture
	SDL_RenderCopyEx(renderer, textures[TEXTURE_FIELD_NUM0], NULL, Rect_FieldNumDest, 0, NULL, SDL_FLIP_NONE);

	//Draw the bottom right set
	//First Draw the left, variable number	
	Rect_FieldNumDest->x = Rect_FieldOfPlay->x + (Rect_FieldOfPlay->w) - (xYards * FieldDimension_Griddy_variableScale->fieldLength / 10) - numMargin - FieldDimension_Griddy_variableScale->numberWidth;
	SDL_RenderCopyEx(renderer, textures[xYards], NULL, Rect_FieldNumDest, 0, NULL, SDL_FLIP_NONE);

	//Next draw the right 0
	Rect_FieldNumDest->x = Rect_FieldOfPlay->x + (Rect_FieldOfPlay->w) - (xYards * FieldDimension_Griddy_variableScale->fieldLength / 10) + numMargin * 2;
	SDL_RenderCopyEx(renderer, textures[TEXTURE_FIELD_NUM0], NULL, Rect_FieldNumDest, 0, NULL, SDL_FLIP_NONE);

	//Top Row
	//First calculate the y value. Remember 
	Rect_FieldNumDest->y = Rect_FieldOfPlay->y + FieldDimension_Griddy_variableScale->numberMargin + FieldDimension_Griddy_variableScale->numberHeight;
	
	//Top Left Pair
	//Top Left - Left 0
	Rect_FieldNumDest->x = Rect_FieldOfPlay->x + (xYards * FieldDimension_Griddy_variableScale->fieldLength / 10) - numMargin - FieldDimension_Griddy_variableScale->numberWidth;
	SDL_RenderCopyEx(renderer, textures[TEXTURE_FIELD_NUM0], NULL, Rect_FieldNumDest, 0, NULL, SDL_FLIP_HORIZONTAL | SDL_FLIP_VERTICAL);
	
	//Top Left - Right Variable
	Rect_FieldNumDest->x = Rect_FieldOfPlay->x + (xYards * FieldDimension_Griddy_variableScale->fieldLength / 10) + numMargin * 2;
	SDL_RenderCopyEx(renderer, textures[xYards], NULL, Rect_FieldNumDest, 0, NULL, SDL_FLIP_HORIZONTAL | SDL_FLIP_VERTICAL);
	
	//Top Right Pair
	//Top Right - Left 0
	Rect_FieldNumDest->x = Rect_FieldOfPlay->x + (Rect_FieldOfPlay->w) - (xYards * FieldDimension_Griddy_variableScale->fieldLength / 10) - numMargin - FieldDimension_Griddy_variableScale->numberWidth;
	SDL_RenderCopyEx(renderer, textures[TEXTURE_FIELD_NUM0], NULL, Rect_FieldNumDest, 0, NULL, SDL_FLIP_HORIZONTAL | SDL_FLIP_VERTICAL);
	
	//Top Right - Right Variable
	Rect_FieldNumDest->x = Rect_FieldOfPlay->x + (Rect_FieldOfPlay->w) - (xYards * FieldDimension_Griddy_variableScale->fieldLength / 10) + numMargin * 2;
	SDL_RenderCopyEx(renderer, textures[xYards], NULL, Rect_FieldNumDest, 0, NULL, SDL_FLIP_HORIZONTAL | SDL_FLIP_VERTICAL);
}

void DrawGriddyFieldNumbers50(SDL_Renderer *renderer, SDL_Rect *Rect_FieldOfPlay, FieldDimension_Griddy *FieldDimension_Griddy_variableScale, SDL_Rect *Rect_FieldNumDest)
{
	int numMargin = 3;	//3 foot margin between end of letter and goal line / irl it's like 6 inches but doesn't look good BUT adjustable for sure
	
	//Bottom
	Rect_FieldNumDest->y = Rect_FieldOfPlay->y + FieldDimension_Griddy_variableScale->fieldWidth - FieldDimension_Griddy_variableScale->numberMargin - FieldDimension_Griddy_variableScale->numberHeight;
	//Bottom Left 5
	Rect_FieldNumDest->x = Rect_FieldOfPlay->x + (Rect_FieldOfPlay->w / 2) - numMargin - FieldDimension_Griddy_variableScale->numberWidth;
	SDL_RenderCopyEx(renderer, textures[TEXTURE_FIELD_NUM5], NULL, Rect_FieldNumDest, 0, NULL, SDL_FLIP_NONE);

	//Bottom Right 0
	Rect_FieldNumDest->x = Rect_FieldOfPlay->x + (Rect_FieldOfPlay->w / 2) + numMargin * 2;
	SDL_RenderCopyEx(renderer, textures[TEXTURE_FIELD_NUM0], NULL, Rect_FieldNumDest, 0, NULL, SDL_FLIP_NONE);

	//Top
	Rect_FieldNumDest->y = Rect_FieldOfPlay->y + FieldDimension_Griddy_variableScale->numberMargin + FieldDimension_Griddy_variableScale->numberHeight;

	//Top Left 0 FLIP
	Rect_FieldNumDest->x = Rect_FieldOfPlay->x + (Rect_FieldOfPlay->w / 2) - numMargin - FieldDimension_Griddy_variableScale->numberWidth;
	SDL_RenderCopyEx(renderer, textures[TEXTURE_FIELD_NUM5], NULL, Rect_FieldNumDest, 0, NULL, SDL_FLIP_HORIZONTAL | SDL_FLIP_VERTICAL);

	//Top Right 5 FLIP
	Rect_FieldNumDest->x = Rect_FieldOfPlay->x + (Rect_FieldOfPlay->w / 2) + numMargin * 2;
	SDL_RenderCopyEx(renderer, textures[TEXTURE_FIELD_NUM0], NULL, Rect_FieldNumDest, 0, NULL, SDL_FLIP_HORIZONTAL | SDL_FLIP_VERTICAL);
}

void TestDrawTexture(SDL_Renderer *renderer)
{
	//SDL_Rect Rect_TestDest;
	//
	//Rect_TestDest.x = -200;
	//Rect_TestDest.y = 50;
	//Rect_TestDest.w = 250; 
	//Rect_TestDest.h = 100;

	//SDL_RenderFillRect(renderer, &Rect_TestDest);

	//SDL_RenderCopyEx(renderer, textures[3], NULL, &Rect_TestDest, 0, NULL, SDL_FLIP_NONE);
}
	
