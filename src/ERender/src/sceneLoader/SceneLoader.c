#include "SceneLoader.h"

bool SceneLoader_load(ERenderSceneInstance_p scene, const char* filename)
{
	return SceneLoader_loadOBJ(scene, filename);
}

_SceneLoader SceneLoader = {
	load: SceneLoader_load,
};