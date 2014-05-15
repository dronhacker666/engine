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

	GLint positionLocation = 0; // GLint positionLocation = glGetAttribLocation(camera->shaderManager->shader_id, "iPosition");
	GLint texcoordLocation = 1; // GLint texcoordLocation = glGetAttribLocation(camera->shaderManager->shader_id, "iTexcoord");

	glVertexAttribPointer(positionLocation, 3, GL_FLOAT, GL_FALSE, 8*sizeof(float), 0);
	glEnableVertexAttribArray(positionLocation);

	glVertexAttribPointer(texcoordLocation, 2, GL_FLOAT, GL_FALSE, 8*sizeof(float), (const GLvoid*)(sizeof(float)*3) );
	glEnableVertexAttribArray(texcoordLocation);

	return true;
}

void ERenderModel_render(ERenderModelInstance_p model, ERenderCameraInstance_p camera)
{
	Matrix4f 
		translationModel,
		rotationModel,
		modelMatrix;

	ERenderMatrix.translation4f(translationModel, model->position.x, model->position.y, model->position.z);
	ERenderMatrix.rotation4f(rotationModel, model->rotation.x, model->rotation.y, model->rotation.z);
	ERenderMatrix.mul4f(modelMatrix, translationModel, rotationModel);
	glUniformMatrix4fv(glGetUniformLocation(camera->shaderManager->shader_id, "modelMatrix"), 1, GL_TRUE, modelMatrix);

	// Textures
	if(model->mtl){
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, model->mtl->tex[0]);
		glUniform1i(glGetUniformLocation(camera->shaderManager->shader_id, "iTex0") , 0);
	}

	/*if(model->texture0){
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, model->texture0);
		glUniform1i(glGetUniformLocation(camera->shaderManager->shader_id, "iTex0") , 0);
	}
	if(model->texture1){
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, model->texture1);
		glUniform1i(glGetUniformLocation(camera->shaderManager->shader_id, "iTex1") , 1);
	}
	if(model->texture2){
		glActiveTexture(GL_TEXTURE2);
		glBindTexture(GL_TEXTURE_2D, model->texture2);
		glUniform1i(glGetUniformLocation(camera->shaderManager->shader_id, "iTex2") , 2);
	}*/

	glBindVertexArray(model->VAO);
	glDrawArrays(GL_TRIANGLES, 0, model->vertexCount);
}

_ERenderModel ERenderModel = {
	create: ERenderModel_create,
	loadMesh: ERenderModel_loadMesh,
	render: ERenderModel_render,
};