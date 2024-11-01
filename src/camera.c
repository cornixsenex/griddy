#include <SDL2/SDL.h>
#include "camera.h"
#include "draw_field.h"
#include "global.h"
#include <stdio.h>

//Global Camera Object
CameraObject griddyCameraObject;

//Setup Camera Object
void InitCameraObject()
{
	//Just set the default camera position
	griddyCameraObject.x = 0;
	griddyCameraObject.y = 0;
	griddyCameraObject.w = 640;
	griddyCameraObject.h = 640;
	griddyCameraObject.scale = 1;
	griddyCameraObject.rotationAngle = 0;
}

void TryTranslateCameraObjectLeft() 
{
	griddyCameraObject.x -= griddyCameraObject.w / 10;
}

void TryTranslateCameraObjectRight()
{
	griddyCameraObject.x += griddyCameraObject.w / 10;
}

void TryTranslateCameraObjectUp()
{
	griddyCameraObject.y -= griddyCameraObject.w / 10;
}

void TryTranslateCameraObjectDown()
{
	griddyCameraObject.y += griddyCameraObject.w / 10;
}

void TryZoomCameraObjectIn()
{
	switch (griddyCameraObject.scale) {
		case 1:
			griddyCameraObject.scale = 2;
			break;
		case 2:
			griddyCameraObject.scale = 5;
			break;
		case 5:
			griddyCameraObject.scale = 10;
			break;
		case 10:
			griddyCameraObject.scale = 20;
			break;
		default:
			break;
	}
	CenterCameraObjectAfterZoomIn();
	//Center XY on the new zoom'd in CameraView
}

void TryZoomCameraObjectOut()
{
	switch (griddyCameraObject.scale) {
		case 1:
			break;
		case 2:
			griddyCameraObject.scale = 1;
			break;
		case 5:
			griddyCameraObject.scale = 2;
			break;
		case 10:
			griddyCameraObject.scale = 5;
			break;
		case 20:
			griddyCameraObject.scale = 10;
			break;
		default:
			break;
	}
	CenterCameraObjectAfterZoomOut();
}

void CenterCameraObjectAfterZoomIn()
{
	printf("========\nCameraObjectData:\n=========\nx:	%f\ny:	%f\nw:	%f\nh:	%f\nscale:  %d\n", griddyCameraObject.x, griddyCameraObject.y, griddyCameraObject.w, griddyCameraObject.h, griddyCameraObject.scale);
	UpdateCameraObjectSize();
	if (griddyCameraObject.scale == 1) {
		griddyCameraObject.x = griddySDL_Data.screenSizeRect.x;
		griddyCameraObject.y = griddySDL_Data.screenSizeRect.y;
	} else {
		griddyCameraObject.x += griddyCameraObject.w / 2;
		griddyCameraObject.y += griddyCameraObject.h / 2;
	}
	printf("========\nCameraObjectData:\n=========\nx:	%f\ny:	%f\nw:	%f\nh:	%f\nscale:  %d\n", griddyCameraObject.x, griddyCameraObject.y, griddyCameraObject.w, griddyCameraObject.h, griddyCameraObject.scale);
}

void CenterCameraObjectAfterZoomOut()
{
	printf("========\nCameraObjectData:\n=========\nx:	%f\ny:	%f\nw:	%f\nh:	%f\nscale:  %d\n", griddyCameraObject.x, griddyCameraObject.y, griddyCameraObject.w, griddyCameraObject.h, griddyCameraObject.scale);
	UpdateCameraObjectSize();	
	if (griddyCameraObject.scale == 1) {
		griddyCameraObject.x = griddySDL_Data.screenSizeRect.x;
		griddyCameraObject.y = griddySDL_Data.screenSizeRect.y;
	} else {
		griddyCameraObject.x -= griddyCameraObject.w / 2;
		griddyCameraObject.y -= griddyCameraObject.h / 2;
	}
	printf("========\nCameraObjectData:\n=========\nx:	%f\ny:	%f\nw:	%f\nh:	%f\nscale:  %d\n", griddyCameraObject.x, griddyCameraObject.y, griddyCameraObject.w, griddyCameraObject.h, griddyCameraObject.scale);
}

void UpdateCameraObjectSize()
{
	SDL_Rect Rect_Layout;
	//Update CameraObject Size
	CalcFieldLayout(&Rect_Layout);
	griddyCameraObject.w = Rect_Layout.w / griddyCameraObject.scale;
	griddyCameraObject.h = Rect_Layout.h / griddyCameraObject.scale;;
}









