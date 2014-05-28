#include <sceneLoader/SceneLoader.h>

ERenderObjectInstance_p SceneLoader_load(ERenderSceneInstance_p scene, const char* filename)
{
	return SceneLoader_loadOBJ(filename);
}

_SceneLoader SceneLoader = {
	load: SceneLoader_load,
};