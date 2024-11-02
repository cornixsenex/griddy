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
	printf("TOP\n");
	UpdateCameraObjectSize();
	SDL_Rect Rect_Layout;
	TestPrintCameraInfo();
	if (griddyCameraObject.scale == 1) {
		griddyCameraObject.x = 0;
		griddyCameraObject.y = 0;
	} else {
		CalcFieldLayout(&Rect_Layout);
		//Undo the translation and zoom shit // Just give me the actual base layout relative to the window size 
		Rect_Layout.x += griddyCameraObject.x;
		Rect_Layout.y += griddyCameraObject.y;
		Rect_Layout.w /= griddyCameraObject.scale;
		Rect_Layout.h /= griddyCameraObject.scale;

		//Now....The camera X is literally the layout width minus the camera width divided by two because the margin is the difference between the camera width and the layout width
		griddyCameraObject.x = (Rect_Layout.w - griddyCameraObject.w) / 2;
		griddyCameraObject.y = (Rect_Layout.h - griddyCameraObject.h) / 2;
	}
	printf("AFTER\n");
	TestPrintCameraInfo();
}

void CenterCameraObjectAfterZoomOut()
{
	UpdateCameraObjectSize();
	SDL_Rect Rect_Layout;
	TestPrintCameraInfo();
	CalcFieldLayout(&Rect_Layout);
}

void UpdateCameraObjectSize()
{
	SDL_Rect Rect_Layout;
	
	CalcFieldLayout(&Rect_Layout);

	griddyCameraObject.w = (float)Rect_Layout.w / griddyCameraObject.scale / griddyCameraObject.scale;
	griddyCameraObject.h = (float)Rect_Layout.h / griddyCameraObject.scale / griddyCameraObject.scale;
}

void TestPrintCameraInfo()
{
	printf("========\nCameraObjectData:\n=========\nx:	%f\ny:	%f\nw:	%f\nh:	%f\nscale:  %d\n", griddyCameraObject.x, griddyCameraObject.y, griddyCameraObject.w, griddyCameraObject.h, griddyCameraObject.scale);
}





