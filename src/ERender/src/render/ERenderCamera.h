#ifndef ERENDERCAMERA_H
#define ERENDERCAMERA_H

#include "ERenderMatrix.h"
#include "ERenderScene.h"
#include "ERenderObject.h"
#include "ERenderShader.h"

typedef struct {
	Vec3f position;
	Vec3f rotation;

	ERenderSceneInstance_p scene;

	ERenderShaderManagerInstance_p shaderManager;

	GLuint depth;
	GLuint color;
	GLuint FBO;

	bool renderDepth;
	bool renderColor;

	// ViewPort
	struct {
		unsigned int width;
		unsigned int height;
	} viewport;

} ERenderCameraInstance, *ERenderCameraInstance_p;

typedef struct {
	ERenderCameraInstance_p (*create) (void);
	void (*renderScene) (ERenderCameraInstance_p, ERenderSceneInstance_p);

	void (*setSize) (ERenderCameraInstance_p, unsigned int, unsigned int);

} _ERenderCamera;
extern _ERenderCamera ERenderCamera;

#endif