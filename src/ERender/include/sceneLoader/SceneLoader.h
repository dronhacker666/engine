#ifndef SCENEDECODER_H
#define SCENEDECODER_H

#include <render/ERenderMath.h>
#include <render/ERenderScene.h>
#include <render/ERenderModel.h>
#include <render/ERenderGroup.h>
#include <render/ERenderMaterial.h>
#include <ELib.h>

ERenderObjectInstance_p SceneLoader_loadOBJ(const char*);

typedef struct {
	ERenderObjectInstance_p (*load) (ERenderSceneInstance_p, const char*);
} _SceneLoader;

extern _SceneLoader SceneLoader;

#endif