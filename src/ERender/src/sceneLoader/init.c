#include "SceneLoader.h"

const SceneInfo_p loadOBJ(const char*);

_SceneLoader SceneLoader = {
	loadOBJ: loadOBJ,
};