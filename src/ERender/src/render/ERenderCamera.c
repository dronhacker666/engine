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

	unsigned int i;
	ERenderObjectInstance_p object;
	for(i=0; i<scene->models->length; i++)
	{
		object = EList.get(scene->models, i);
		switch(object->type){
			case ERENDEROBJECTTYPE_GROUP:

			break;
			case ERENDEROBJECTTYPE_MODEL:
				ERenderModel.render((ERenderModelInstance_p)object, camera);
			break;
			case ERENDEROBJECTTYPE_LIGHT:

			break;
		}
	}
}

_ERenderCamera ERenderCamera = {
	create: ERenderCameraCreate,
	renderScene: ERenderCameraRenderScene,
};