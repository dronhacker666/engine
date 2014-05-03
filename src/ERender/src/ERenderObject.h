#ifndef ERENDEROBJECT_H
#define ERENDEROBJECT_H

#include "ERenderTypes.h"
#include "ERenderMatrix.h"
#include "ERenderShader.h"
#include "../../ELib/include/ELib.h"

typedef float *CRenderMesh;

typedef struct {
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
	bool						(*loadTexture)		(ERenderObjectInstance_p, char*, int);
} _ERenderObject;
extern _ERenderObject ERenderObject;

#endif