#ifndef ESCENE_H
#define ESCENE_H

#include "../../ELib/include/ELib.h"
#include "../src/ERenderObject.h"

typedef struct {
	EArray child;
} ERenderSceneInstance, *ERenderSceneInstance_p;

#endif