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

	// ViewPort
	int viewport_x;
	int viewport_y;
	int viewport_width;
	int viewport_height;

} ERenderCameraInstance, *ERenderCameraInstance_p;

typedef struct {
	ERenderCameraInstance_p (*create) (void);
	void (*renderScene) (ERenderCameraInstance_p, ERenderSceneInstance_p);
} _ERenderCamera;
extern _ERenderCamera ERenderCamera;

#endif