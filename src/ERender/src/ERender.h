#ifndef ERENDER_H
#define ERENDER_H

// INCLUDES
#include <windows.h>
#include <GL/GL.h>
#include <GL/wglext.h>
#include <GL/glext.h>
#include "../src/ERenderScene.h"
#include "../src/ERenderShader.h"

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
	ESceneInstance_p scene;

	//Shaders
	ERenderShaderProgram_p shader;

	// ViewPort
	int viewport_x;
	int viewport_y;
	int viewport_width;
	int viewport_height;
} ERenderInstance, *ERenderInstance_p;

typedef struct {
	ERenderInstance_p 	(*create)		(ERenderCreateOptions_p);
	void 				(*render)		(ERenderInstance_p);
	void 				(*setScene)		(ERenderInstance_p, ESceneInstance_p);
	ESceneInstance_p	(*createScene)	(void);
} _ERender;
extern _ERender ERender;


#endif