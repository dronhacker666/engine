#ifndef ERENDEROBJECT_H
#define ERENDEROBJECT_H

#include "ERenderMacro.h"
#include "ERenderTypes.h"
#include "ERenderMatrix.h"
#include "ERenderShader.h"
#include "ELib.h"

typedef float *CRenderMesh;

typedef struct ERenderObjectInstance {
	struct ERenderObjectInstance* _next;
	struct ERenderObjectInstance* _prev;

	ERenderPos pos;

	GLuint texture0;
	GLuint texture1;
	GLuint texture2;

	ERenderShaderInstance_p fragmentShader;
	ERenderShaderInstance_p vertexShader;

	struct {
		GLuint VAO;
		GLuint positionVBO;
		GLuint texcoordVBO;
		GLuint indexVBO;
		GLuint countIndexes;
	} _sys;

	Matrix4f modelMatrix;

} ERenderObjectInstance, *ERenderObjectInstance_p;


typedef struct {
	struct {float* data; unsigned int length;} position;
	struct {float* data; unsigned int length;} texcoord;
	struct {float* data; unsigned int length;} index;
} MeshData, *MeshData_p;


typedef struct {
	ERenderObjectInstance_p 	(*createFromMesh) 	(MeshData_p);
	BOOL						(*loadTexture)		(ERenderObjectInstance_p, char*, int);
} _ERenderObject;
extern _ERenderObject ERenderObject;

#endif