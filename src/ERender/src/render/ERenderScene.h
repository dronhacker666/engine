#ifndef ERENDERSCENE_H
#define ERENDERSCENE_H

#include "ELib.h"
#include "ERenderMacro.h"
#include "ERenderObject.h"

typedef struct ERenderSceneInstance{

	ERenderObjectInstance_p _objects_head;
	ERenderObjectInstance_p _objects_current;

	/*
	ERenderLightInstance_p _lights_head;
	ERenderLightInstance_p _lights_current;
	*/
} ERenderSceneInstance, *ERenderSceneInstance_p;

typedef struct{
	ERenderSceneInstance_p 	(*create) 		(void);
	void 					(*addObject) 	(ERenderSceneInstance_p, ERenderObjectInstance_p);
	void 					(*addLight) 	(ERenderSceneInstance_p, ERenderObjectInstance_p);
} _ERenderScene;
extern _ERenderScene ERenderScene;

#endif