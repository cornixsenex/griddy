#include <SDL2/SDL.h>
#include "camera.h"
#include "global.h"

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
	griddyCameraObject.x -= 10;
}

void TryTranslateCameraObjectRight()
{
	griddyCameraObject.x += 10;

}

void TryTranslateCameraObjectUp()
{
	griddyCameraObject.y -= 10;

}

void TryTranslateCameraObjectDown()
{
	griddyCameraObject.y += 10;

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
}
