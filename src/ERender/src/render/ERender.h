#ifndef ERENDER_H
#define ERENDER_H

struct ERenderInstance;

#include <windows.h>
#include "ERenderEvents.h"
#include "ERenderScene.h"
#include "ERenderCamera.h"

typedef struct {
	// Base
	HWND hWnd;
	HDC hdc;
} GAPI, *GAPI_p;

typedef struct ERenderInstance{
	GAPI gAPI;
	int width;
	int height;

	EEventManager_p 		events;
	ERenderCameraInstance_p camera;
	ERenderSceneInstance_p 	scene;

	float timerFix;

} ERenderInstance, *ERenderInstance_p;

// EVENTS
typedef struct {
	EventPrototype;
	ERenderInstance* render;
} RenderEvent, *RenderEvent_p;


typedef struct {
	ERenderInstance_p 	(*create)		(int, int);
	void 				(*render)		(ERenderInstance_p);
	void 				(*setScene)		(ERenderInstance_p, ERenderSceneInstance_p);
} _ERender;
extern _ERender ERender;


#endif