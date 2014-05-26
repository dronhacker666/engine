#include "ERenderModel.h"
#include "ERenderOpenGL.h"

ERenderModelInstance_p ERenderModel_create(void)
{
	ERenderModelInstance_p model = EMem.alloc(sizeof(ERenderModelInstance));
	model->type = ERENDEROBJECTTYPE_MODEL;
	return model;
}

bool ERenderModel_loadMesh(ERenderModelInstance_p model, unsigned int vertexCount, void* mesh)
{
	model->vertexCount = vertexCount;

	glGenVertexArrays(1, &model->VAO);
	glBindVertexArray(model->VAO);

	glGenBuffers(1, &model->VBO);
	glBindBuffer(GL_ARRAY_BUFFER, model->VBO);
	glBufferData(GL_ARRAY_BUFFER, vertexCount * sizeof(float) * 8, mesh, GL_STATIC_DRAW);

	return true;
}


_ERenderModel ERenderModel = {
	create: ERenderModel_create,
	loadMesh: ERenderModel_loadMesh,
};