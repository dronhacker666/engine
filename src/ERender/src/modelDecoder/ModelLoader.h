#ifndef MODELDECODER_H
#define MODELDECODER_H

#include "ELib.h"

typedef struct {
	void* mesh;
	unsigned int vertexCount;
} Model, *Model_p;

typedef struct {
	const Model_p (*loadOBJ) (const char*);
} _ModelLoader;

extern _ModelLoader ModelLoader;

#endif