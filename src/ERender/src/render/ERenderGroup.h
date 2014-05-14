#ifndef ERENDERGROUP_H
#define ERENDERGROUP_H

#include "ERenderObject.h"

typedef struct ERenderGroupInstance {
	ERenderObjectInstance _prototype;
	ERenderObjectPrototype_p head;
	ERenderObjectPrototype_p current;
} ERenderGroupInstance, *ERenderGroupInstance_p;

typedef struct {
	ERenderGroupInstance_p (*create) (void);
	void (*push) (ERenderGroupInstance_p, ERenderObjectPrototype_p);
} _ERendeGroup;
extern _ERendeGroup ERendeGroup;

#endif