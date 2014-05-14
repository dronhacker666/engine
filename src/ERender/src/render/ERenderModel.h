#ifndef ERENDERMODEL_H
#define ERENDERMODEL_H

#include "ERenderObject.h"
#include "ERenderCamera.h"

typedef struct {
	char* name;
	void* mesh;
	unsigned int vertexCount;
} MeshInfo, *MeshInfo_p;

typedef struct {
	ERenderObjectPrototype;

	GLuint texture0;
	GLuint texture1;
	GLuint texture2;

	ERenderShaderInstance_p fragmentShader;
	ERenderShaderInstance_p vertexShader;

	GLuint VAO;
	GLuint VBO;
	GLuint vertexCount;

	Matrix4f modelMatrix;

} ERenderModelInstance, *ERenderModelInstance_p;


typedef struct {
	ERenderModelInstance_p (*create) (MeshInfo_p);
	void (*render) (ERenderModelInstance_p, ERenderCameraInstance_p);
} _ERenderModel;
extern _ERenderModel ERenderModel;

#endif