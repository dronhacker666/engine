#ifndef ERENDERGROUP_H
#define ERENDERGROUP_H

#include "ERenderObject.h"

typedef struct ERenderGroupInstance {
	ERenderObjectPrototype;

	EListInstance_p child;
} ERenderGroupInstance, *ERenderGroupInstance_p;

typedef struct {
	ERenderGroupInstance_p (*create) (void);
} _ERenderGroup;
extern _ERenderGroup ERenderGroup;

#endif