#ifndef SCENEDECODER_H
#define SCENEDECODER_H

#include "ERenderMath.h"
#include "ERenderModel.h"
#include "ELib.h"

typedef struct {
	Vec3f position;
	Vec3f direction;
} LightInfo, *LightInfo_p;

typedef struct {
	MeshInfo *meshes;
	unsigned int meshCount;
} SceneInfo, *SceneInfo_p;

typedef struct {
	const SceneInfo_p (*loadOBJ) (const char*);
} _SceneLoader;

extern _SceneLoader SceneLoader;

#endif