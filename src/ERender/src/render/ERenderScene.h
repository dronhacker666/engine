#ifndef ERENDERSCENE_H
#define ERENDERSCENE_H

#include "ELib.h"
#include "ERenderMacro.h"

typedef struct ERenderSceneInstance{
	EArray child;
} ERenderSceneInstance, *ERenderSceneInstance_p;

typedef struct{
	ERenderSceneInstance_p (*create) (void);
} _ERenderScene;
extern _ERenderScene ERenderScene;

#endif