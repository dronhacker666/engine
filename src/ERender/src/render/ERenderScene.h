#ifndef ERENDERSCENE_H
#define ERENDERSCENE_H

#include "ELib.h"
#include "ERenderObject.h"

typedef struct ERenderSceneItem {
	struct ERenderSceneItem* prev;
	ERenderObjectInstance_p this;
	struct ERenderSceneItem* next;
} ERenderSceneItem, *ERenderSceneItem_p;


typedef struct{
	ERenderSceneItem_p _head;
	ERenderSceneItem_p _current;

} ERenderSceneInstance, *ERenderSceneInstance_p;

typedef struct{
	ERenderSceneInstance_p 	(*create) 		(void);
	void 					(*addObject) 	(ERenderSceneInstance_p, ERenderObjectInstance_p);

	bool					(*load)			(ERenderSceneInstance_p, const char*);

} _ERenderScene;
extern _ERenderScene ERenderScene;

#endif