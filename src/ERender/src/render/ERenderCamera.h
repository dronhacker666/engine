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
	struct {
		int width;
		int height;
		int x;
		int y;
	} viewport;

} ERenderCameraInstance, *ERenderCameraInstance_p;

typedef struct {
	ERenderCameraInstance_p (*create) (void);
	void (*renderScene) (ERenderCameraInstance_p, ERenderSceneInstance_p);
} _ERenderCamera;
extern _ERenderCamera ERenderCamera;

#endif