#include "ERenderScene.h"

ERenderSceneInstance_p ERenderScene_create(void)
{
	new(scene, ERenderSceneInstance);
	return scene;
}

void ERenderScene_addObject(ERenderSceneInstance_p scene, ERenderObjectInstance_p object)
{
	object->_next = NULL;
	object->_prev = scene->_objects_current;

	if(scene->_objects_head==NULL){
		scene->_objects_head = object;
	}
	if(scene->_objects_current!=NULL){
		scene->_objects_current->_next = object;
	}
	scene->_objects_current = object;
}

_ERenderScene ERenderScene = {
	create: ERenderScene_create,
	addObject: ERenderScene_addObject,
};