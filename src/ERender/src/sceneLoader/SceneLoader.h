#ifndef SCENEDECODER_H
#define SCENEDECODER_H

#include "ERenderMath.h"
#include "ERenderScene.h"
#include "ERenderModel.h"
#include "ERenderMaterial.h"
#include "ELib.h"

bool SceneLoader_loadOBJ(ERenderSceneInstance_p, const char*);

typedef struct {
	bool (*load) (ERenderSceneInstance_p, const char*);
} _SceneLoader;

extern _SceneLoader SceneLoader;

#endif