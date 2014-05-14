#include "ERenderScene.h"
#include "../sceneLoader/SceneLoader.h"

ERenderSceneInstance_p ERenderScene_create(void)
{
	ERenderSceneInstance_p scene = EMem.alloc(sizeof(ERenderSceneInstance));

	return scene;
}

void ERenderScene_addObject(ERenderSceneInstance_p scene, ERenderObjectInstance_p object)
{
	ERenderSceneItem_p item = EMem.alloc(sizeof(ERenderSceneItem));

	item->this = object;
	item->next = NULL;
	item->prev = scene->_current;

	if(scene->_head==NULL){
		scene->_head = item;
	}
	if(scene->_current!=NULL){
		scene->_current->next = item;
	}
	scene->_current = item;
}


bool ERenderScene_load(ERenderSceneInstance_p scene, const char* filename)
{
	SceneInfo_p sceneInfo = SceneLoader.loadOBJ(filename);

	int i;
	for(i=0; i<sceneInfo->meshCount; i++)
	{
		ERenderScene_addObject(
			scene,
			(ERenderObjectInstance_p)ERenderModel.create(&sceneInfo->meshes[i])
		);
	}
}

_ERenderScene ERenderScene = {
	create: ERenderScene_create,
	addObject: ERenderScene_addObject,
	load: ERenderScene_load,
};