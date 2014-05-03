#include "ERenderCamera.h"
#include "ERenderOpenGL.h"

ERenderCameraInstance_p ERenderCameraCreate(void)
{
	ERenderCameraInstance_p camera = malloc(sizeof(ERenderCameraInstance));

	camera->shaderManager = ERenderShaderManager.create();

	camera->pos.z = -10;
	camera->pos.rx = 0.1;

	return camera;
}


void ERenderCameraRenderObject(ERenderCameraInstance_p camera, ERenderObjectInstance_p object)
{
	ERenderShaderManager.prepareShaders(camera->shaderManager);

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
	ERenderMatrix.translation4f(translationView, camera->pos.x, camera->pos.y, camera->pos.z);
	ERenderMatrix.rotation4f(rotationView, camera->pos.rx/100, camera->pos.ry/100, camera->pos.rz/100);
	ERenderMatrix.mul4f(rotationView, rotationView, translationView);
	ERenderMatrix.mul4f(viewProjectionMatrix, projectionMatrix, rotationView);

	ERenderMatrix.translation4f(translationModel, object->pos.x, object->pos.y, object->pos.z);
	ERenderMatrix.rotation4f(rotationModel, object->pos.rx/100, object->pos.ry/100, object->pos.rz/100);
	ERenderMatrix.mul4f(modelMatrix, translationModel, rotationModel);

	glUniformMatrix4fv(glGetUniformLocation(camera->shaderManager->shader_id, "viewMatrix"), 1, GL_TRUE, viewProjectionMatrix);
	glUniformMatrix4fv(glGetUniformLocation(camera->shaderManager->shader_id, "modelMatrix"), 1, GL_TRUE, modelMatrix);


	glBindBuffer(GL_ARRAY_BUFFER, object->_sys.positionVBO);
	GLint positionLocation = glGetAttribLocation(camera->shaderManager->shader_id, "iPosition");
	if(positionLocation !=-1 ){
		glVertexAttribPointer(positionLocation, 3, GL_FLOAT, GL_FALSE, 3*sizeof(float), 0);
		glEnableVertexAttribArray(positionLocation);
	}

	glBindBuffer(GL_ARRAY_BUFFER, object->_sys.texcoordVBO);
	GLint texcoordLocation = glGetAttribLocation(camera->shaderManager->shader_id, "iTexcoord");
	if(texcoordLocation !=-1 ){
		glVertexAttribPointer(texcoordLocation, 2, GL_FLOAT, GL_FALSE, 2*sizeof(float), 0);
		glEnableVertexAttribArray(texcoordLocation);
	}

	glBindVertexArray(object->_sys.VAO);

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

	glDrawElements(GL_TRIANGLES, object->_sys.countIndexes, GL_UNSIGNED_INT, NULL);
}


void ERenderCameraRenderScene(ERenderCameraInstance_p camera, ERenderSceneInstance_p scene)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	int i;
	for(i=0; i<scene->child->length; i++){
		ERenderCameraRenderObject(camera, (ERenderObjectInstance_p)*(void**)eArray.get(scene->child, i) );
	}
}

_ERenderCamera ERenderCamera = {
	create: ERenderCameraCreate,
	renderScene: ERenderCameraRenderScene,
};