#ifndef ERENDEROBJECT_H
#define ERENDEROBJECT_H

#include "ERenderTypes.h"
#include "ERenderMatrix.h"
#include "ERenderShader.h"

typedef float *CRenderMesh;

typedef struct {
	ERenderPos pos;
	
	ERenderShaderInstance_p fragmentShader;
	ERenderShaderInstance_p vertexShader;

	GLuint meshVAO;
	GLuint meshVBO;

	Matrix4f modelMatrix;

} ERenderObjectInstance, *ERenderObjectInstance_p;


typedef struct {
	ERenderObjectInstance_p (*createFromMesh) (CRenderMesh, unsigned int);
} _ERenderObject;
extern _ERenderObject ERenderObject;

#endif