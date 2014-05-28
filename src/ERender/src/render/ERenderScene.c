#include <render/ERenderScene.h>
#include <sceneLoader/SceneLoader.h>

ERenderSceneInstance_p ERenderScene_create(void)
{
	ERenderSceneInstance_p scene = EMem.alloc(sizeof(ERenderSceneInstance));
	scene->models = EList.create();
	scene->lights = EList.create();
	return scene;
}

void ERenderScene_addObject(ERenderSceneInstance_p scene, ERenderObjectInstance_p object)
{
	switch(object->type){
		case ERENDEROBJECTTYPE_GROUP:
		case ERENDEROBJECTTYPE_MODEL:
			EList.push(scene->models, object);
		break;
		case ERENDEROBJECTTYPE_LIGHT:
			EList.push(scene->lights, object);
		break;
	}
}


ERenderObjectInstance_p ERenderScene_load(ERenderSceneInstance_p scene, const char* filename)
{
	ERenderObjectInstance_p object = SceneLoader.load(scene, filename);
	ERenderScene_addObject(scene, object);
	return object;
}

_ERenderScene ERenderScene = {
	create: ERenderScene_create,
	addObject: ERenderScene_addObject,
	load: ERenderScene_load,
};