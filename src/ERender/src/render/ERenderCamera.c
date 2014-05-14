#include "ERenderCamera.h"
#include "ERenderOpenGL.h"
#include "ERenderModel.h"

ERenderCameraInstance_p ERenderCameraCreate(void)
{
	ERenderCameraInstance_p camera = EMem.alloc(sizeof(ERenderCameraInstance));

	camera->shaderManager = ERenderShaderManager.create();

	camera->position.z = -10;

	return camera;
}

/*
void ERenderCameraRenderObject(ERenderCameraInstance_p camera, ERenderObjectInstance_p object)
{
	ERenderShaderManager.prepareShaders(camera->shaderManager);

	// TODO: move out this from render loop
	if(some==1){
		glBindVertexArray(object->_sys.VAO);
		
		glBindBuffer(GL_ARRAY_BUFFER, object->_sys.VBO);

		GLint positionLocation = glGetAttribLocation(camera->shaderManager->shader_id, "iPosition");
		if(positionLocation !=-1 ){
			glVertexAttribPointer(positionLocation, 3, GL_FLOAT, GL_FALSE, 8*sizeof(float), 0);
			glEnableVertexAttribArray(positionLocation);
		}

		GLint texcoordLocation = glGetAttribLocation(camera->shaderManager->shader_id, "iTexcoord");
		if(texcoordLocation !=-1 ){
			glVertexAttribPointer(texcoordLocation, 2, GL_FLOAT, GL_FALSE, 8*sizeof(float), (const GLvoid*)(sizeof(float)*3) );
			glEnableVertexAttribArray(texcoordLocation);
		}

		some=2;
	}


	Matrix4f 
		projectionMatrix,

		translationView,
		rotationView,

		translationModel,
		rotationModel,

		viewProjectionMatrix,
		modelMatrix
	;

	float aspectRatio = (float)800 / (float)600;
	ERenderMatrix.perspective4f(projectionMatrix, 45.0f, aspectRatio, 0.01f, 500.0f);

	ERenderMatrix.translation4f(translationView, camera->position.x, camera->position.y, camera->position.z);
	ERenderMatrix.rotation4f(rotationView, camera->rotation.x, camera->rotation.y, camera->rotation.z);
	ERenderMatrix.mul4f(rotationView, rotationView, translationView);
	ERenderMatrix.mul4f(viewProjectionMatrix, projectionMatrix, rotationView);

	ERenderMatrix.translation4f(translationModel, object->position.x, object->position.y, object->position.z);
	ERenderMatrix.rotation4f(rotationModel, object->rotation.x, object->rotation.y, object->rotation.z);
	ERenderMatrix.mul4f(modelMatrix, translationModel, rotationModel);

	glUniformMatrix4fv(glGetUniformLocation(camera->shaderManager->shader_id, "viewMatrix"), 1, GL_TRUE, viewProjectionMatrix);
	glUniformMatrix4fv(glGetUniformLocation(camera->shaderManager->shader_id, "modelMatrix"), 1, GL_TRUE, modelMatrix);

	// Textures
	if(object->texture0){
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, object->texture0);
		glUniform1i(glGetUniformLocation(camera->shaderManager->shader_id, "iTex0") , 0);
	}
	if(object->texture1){
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, object->texture1);
		glUniform1i(glGetUniformLocation(camera->shaderManager->shader_id, "iTex1") , 1);
	}
	if(object->texture2){
		glActiveTexture(GL_TEXTURE2);
		glBindTexture(GL_TEXTURE_2D, object->texture2);
		glUniform1i(glGetUniformLocation(camera->shaderManager->shader_id, "iTex2") , 2);
	}

	glBindVertexArray(object->_sys.VAO);

	glDrawArrays(GL_TRIANGLES, 0, object->_sys.vertexCount);
}
*/


void ERenderCameraRenderScene(ERenderCameraInstance_p camera, ERenderSceneInstance_p scene)
{
	ERenderShaderManager.prepareShaders(camera->shaderManager);

	Matrix4f 
		rotationView,
		translationView,
		projectionMatrix,
		viewProjectionMatrix;

	float aspectRatio = (float)800 / (float)600;
	ERenderMatrix.perspective4f(projectionMatrix, 45.0f, aspectRatio, 0.01f, 500.0f);

	ERenderMatrix.translation4f(translationView, camera->position.x, camera->position.y, camera->position.z);
	ERenderMatrix.rotation4f(rotationView, camera->rotation.x, camera->rotation.y, camera->rotation.z);
	ERenderMatrix.mul4f(rotationView, rotationView, translationView);
	ERenderMatrix.mul4f(viewProjectionMatrix, projectionMatrix, rotationView);
	glUniformMatrix4fv(glGetUniformLocation(camera->shaderManager->shader_id, "viewMatrix"), 1, GL_TRUE, viewProjectionMatrix);


	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	ERenderSceneItem_p item = scene->_head;
	while(item){
		switch(item->this->type){
			case ERENDEROBJECTTYPE_GROUP:

			break;
			case ERENDEROBJECTTYPE_MODEL:
				ERenderModel.render((ERenderModelInstance_p)item->this, camera);
			break;
			case ERENDEROBJECTTYPE_LIGHT:

			break;
		}

		item = item->next;
	}
}

_ERenderCamera ERenderCamera = {
	create: ERenderCameraCreate,
	renderScene: ERenderCameraRenderScene,
};