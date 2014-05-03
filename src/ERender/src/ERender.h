#ifndef ERENDER_H
#define ERENDER_H


#include <windows.h>
#include "ERenderObject.h"
#include "ERenderCamera.h"
#include "ERenderScene.h"
#include "ERenderShader.h"

typedef struct {
	int width;
	int height;
	char* title;
} ERenderCreateOptions, *ERenderCreateOptions_p;

typedef struct {
	// Base
	HWND hWnd;
	HDC hdc;
} GAPI;

typedef struct {
	GAPI gAPI;

	// Camera
	ERenderCameraInstance_p camera;
	// Rendered Scene
	ERenderSceneInstance_p scene;

} ERenderInstance, *ERenderInstance_p;

typedef struct {
	ERenderInstance_p 	(*create)		(ERenderCreateOptions_p);
	void 				(*render)		(ERenderInstance_p);
	void 				(*setScene)		(ERenderInstance_p, ERenderSceneInstance_p);
} _ERender;
extern _ERender ERender;


#endif