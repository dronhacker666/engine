#include "ModelLoader.h"

const Model_p loadOBJ(const char*);

_ModelLoader ModelLoader = {
	loadOBJ: loadOBJ,
};