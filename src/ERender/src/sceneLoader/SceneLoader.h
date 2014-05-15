#ifndef SCENEDECODER_H
#define SCENEDECODER_H

#include "ERenderMath.h"
#include "ERenderScene.h"
#include "ERenderModel.h"
#include "ERenderGroup.h"
#include "ERenderMaterial.h"
#include "ELib.h"

ERenderObjectInstance_p SceneLoader_loadOBJ(const char*);

typedef struct {
	ERenderObjectInstance_p (*load) (ERenderSceneInstance_p, const char*);
} _SceneLoader;

extern _SceneLoader SceneLoader;

#endif