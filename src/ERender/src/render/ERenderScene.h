#ifndef ERENDERSCENE_H
#define ERENDERSCENE_H

#include "ELib.h"
#include "ERenderObject.h"

typedef struct{

	EListInstance_p models;
	EListInstance_p lights;

} ERenderSceneInstance, *ERenderSceneInstance_p;

typedef struct{
	ERenderSceneInstance_p 	(*create) 		(void);
	void 					(*addObject) 	(ERenderSceneInstance_p, ERenderObjectInstance_p);

	bool					(*load)			(ERenderSceneInstance_p, const char*);

} _ERenderScene;
extern _ERenderScene ERenderScene;

#endif