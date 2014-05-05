#ifndef ERENDER_H
#define ERENDER_H

#include <windows.h>
#include "EInput.h"
#include "ERenderObject.h"
#include "ERenderCamera.h"
#include "ERenderScene.h"
#include "ERenderShader.h"
#include "ERenderEvents.h"

typedef struct {
	// Base
	HWND hWnd;
	HDC hdc;
} GAPI, *GAPI_p;

typedef struct {
	GAPI gAPI;
	int width;
	int height;

	EEventManager_p events;

	// Camera
	ERenderCameraInstance_p camera;
	// Rendered Scene
	ERenderSceneInstance_p scene;

} ERenderInstance, *ERenderInstance_p;

typedef struct {
	ERenderInstance_p 	(*create)		(int, int);
	void 				(*render)		(ERenderInstance_p);
	void 				(*setScene)		(ERenderInstance_p, ERenderSceneInstance_p);
} _ERender;
extern _ERender ERender;


#endif