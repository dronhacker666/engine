#include "ERenderScene.h"

ERenderSceneInstance_p ERenderScene_create(void)
{
	new(scene, ERenderSceneInstance);
	scene->child = eArray.create(sizeof(void*));
	return scene;
}

_ERenderScene ERenderScene = {
	create: ERenderScene_create,
};