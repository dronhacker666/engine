#ifndef ERENDERMODEL_H
#define ERENDERMODEL_H

#include "ERenderObject.h"
#include "ERenderCamera.h"
#include "ERenderMaterial.h"

typedef struct {
	ERenderObjectPrototype;

	char* name;

	ERenderMaterialInstance_p mtl;

	ERenderShaderInstance_p fragmentShader;
	ERenderShaderInstance_p vertexShader;

	GLuint VAO;
	GLuint VBO;
	GLuint vertexCount;

	Matrix4f modelMatrix;

} ERenderModelInstance, *ERenderModelInstance_p;


typedef struct {
	ERenderModelInstance_p 	(*create) 		(void);
	bool 					(*loadMesh) 	(ERenderModelInstance_p, unsigned int, void*);
} _ERenderModel;
extern _ERenderModel ERenderModel;

#endif