#ifndef ERENDEROBJECT_H
#define ERENDEROBJECT_H

#include "ERenderShader.h"
#include "ERenderMatrix.h"
#include "ERenderMath.h"
#include "ELib.h"

typedef enum {
	ERENDEROBJECTTYPE_GROUP,
	ERENDEROBJECTTYPE_MODEL,
	ERENDEROBJECTTYPE_LIGHT,
} ERenderObjectType;

#define ERenderObjectPrototype \
	ERenderObjectType type;\
	Vec3f position;\
	Vec3f rotation;

typedef struct {
	ERenderObjectPrototype;
} ERenderObjectInstance, *ERenderObjectInstance_p;

#endif