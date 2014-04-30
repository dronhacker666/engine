#ifndef ERENDEROBJECT_H
#define ERENDEROBJECT_H

#include "../src/ERenderShader.h"

typedef struct {
	ERenderShaderInstance_p fragmentShader;
	ERenderShaderInstance_p vertexShader;

	GLuint vbo;

} ERenderObjectInstance, *ERenderObjectInstance_p;

#endif