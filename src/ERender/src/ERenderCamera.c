#include "ERenderCamera.h"
#include "ERenderOpenGL.h"

ERenderCameraInstance_p ERenderCameraCreate(void)
{
	ERenderCameraInstance_p camera = malloc(sizeof(ERenderCameraInstance));

	camera->shaderManager = ERenderShaderManager.create();

	camera->pos.z = 10;
	camera->pos.rx = 0.1;

	return camera;
}


void ERenderCameraRenderObject(ERenderCameraInstance_p camera, ERenderObjectInstance_p object)
{
	ERenderShaderManager.prepareShaders(camera->shaderManager);

	Matrix4f 
		tempMatrix,
		viewMatrix,
		modelMatrix
	;

	ERenderMatrix.translation4f(viewMatrix, camera->pos.x, camera->pos.y, camera->pos.z);
	ERenderMatrix.rotation4f(tempMatrix, camera->pos.rx/100, camera->pos.ry/100, camera->pos.rz/100 );
	ERenderMatrix.mul4f(viewMatrix, tempMatrix, viewMatrix);

	float aspectRatio = (float)800 / (float)600;
	ERenderMatrix.perspective4f(tempMatrix, 45.0f, aspectRatio, 0.1f, 500.0f);
	ERenderMatrix.mul4f(viewMatrix, tempMatrix, viewMatrix);


	ERenderMatrix.translation4f(modelMatrix, object->pos.x, object->pos.y, object->pos.z);
	ERenderMatrix.rotation4f(tempMatrix, object->pos.rx/100, object->pos.ry/100, object->pos.rz/100 );
	ERenderMatrix.mul4f(modelMatrix, modelMatrix, tempMatrix);


	glUniformMatrix4fv(glGetUniformLocation(camera->shaderManager->shader_id, "viewMatrix"), 1, GL_TRUE, viewMatrix);
	glUniformMatrix4fv(glGetUniformLocation(camera->shaderManager->shader_id, "modelMatrix"), 1, GL_TRUE, modelMatrix);

	GLint positionLocation = glGetAttribLocation(camera->shaderManager->shader_id, "position");
	if (positionLocation != -1)
	{
		glVertexAttribPointer(positionLocation, 3, GL_FLOAT, GL_FALSE, 12, 0);
		glEnableVertexAttribArray(positionLocation);
	}

	glBindVertexArray(object->meshVAO);
	glBindBuffer(GL_ARRAY_BUFFER, object->meshVBO);
	glDrawArrays(GL_TRIANGLES, 0, 3);
}


void ERenderCameraRenderScene(ERenderCameraInstance_p camera, ERenderSceneInstance_p scene)
{
	glClearColor(0.8, 0.8, 0.8, 0.0);
	glShadeModel(GL_FLAT);
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