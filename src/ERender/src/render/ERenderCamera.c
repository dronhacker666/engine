#include "ERenderCamera.h"
#include "ERenderOpenGL.h"
#include "ERenderModel.h"
#include "ERenderGroup.h"

ERenderCameraInstance_p ERenderCamera_create(void)
{
	ERenderCameraInstance_p camera = EMem.alloc(sizeof(ERenderCameraInstance));

	camera->renderDepth = true;
	camera->renderColor = true;

	glGenFramebuffers(1, &camera->FBO);

	camera->shaderManager = ERenderShaderManager.create();

	camera->position.z = -10;

	return camera;
}

void ERenderCamera_freeTextures(ERenderCameraInstance_p camera)
{
	if(camera->depth){
		glDeleteTextures(1, &camera->depth);
	}
	if(camera->color){
		glDeleteTextures(1, &camera->color);
	}
}

void ERenderCamera_setSize(ERenderCameraInstance_p camera, unsigned int width, unsigned int height)
{
	glBindFramebuffer(GL_FRAMEBUFFER, camera->FBO);
	if(
		camera->viewport.width != width ||
		camera->viewport.height != height
	){
		ERenderCamera_freeTextures(camera);
		if(camera->renderDepth){
			camera->depth = TextureCreate(GL_DEPTH_COMPONENT24, GL_DEPTH_COMPONENT, width, height, NULL, false);
			glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, camera->depth, 0);
		}
		if(camera->renderColor){
			glDrawBuffer(GL_BACK);
			glReadBuffer(GL_BACK);
			camera->color = TextureCreate(GL_RGBA8, GL_RGB, width, height, NULL, false);
			glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, camera->color, 0);
		}else{
			glDrawBuffer(GL_NONE);
			glReadBuffer(GL_NONE);
		}
	}
	camera->viewport.width = width;
	camera->viewport.height = height;
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}


void ERenderCamera_render(ERenderCameraInstance_p camera, EListInstance_p objects)
{
	unsigned int i;
	ERenderObjectInstance_p object;
	for(i=0; i<objects->length; i++)
	{
		object = EList.get(objects, i);
		switch(object->type){
			case ERENDEROBJECTTYPE_GROUP:
				ERenderCamera_render(camera, ((ERenderGroupInstance_p)object)->child );
			break;
			case ERENDEROBJECTTYPE_MODEL:
				ERenderModel.render( (ERenderModelInstance_p)object, camera );
			break;
			case ERENDEROBJECTTYPE_LIGHT:

			break;
		}
	}
}

void ERenderCamera_renderScene(ERenderCameraInstance_p camera, ERenderSceneInstance_p scene)
{
	ERenderShaderManager.prepareShaders(camera->shaderManager);

	Matrix4f 
		rotationView,
		translationView,
		projectionMatrix,
		viewProjectionMatrix;

	float aspectRatio = (float)camera->viewport.width / (float)camera->viewport.height;
	ERenderMatrix.perspective4f(projectionMatrix, 45.0f, aspectRatio, 0.01f, 500.0f);

	ERenderMatrix.translation4f(translationView, camera->position.x, camera->position.y, camera->position.z);
	ERenderMatrix.rotation4f(rotationView, camera->rotation.x, camera->rotation.y, camera->rotation.z);
	ERenderMatrix.mul4f(rotationView, rotationView, translationView);
	ERenderMatrix.mul4f(viewProjectionMatrix, projectionMatrix, rotationView);
	glUniformMatrix4fv(glGetUniformLocation(camera->shaderManager->shader_id, "viewMatrix"), 1, GL_TRUE, viewProjectionMatrix);

	glBindFramebuffer(GL_FRAMEBUFFER, camera->FBO);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	ERenderCamera_render(camera, scene->models);

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

_ERenderCamera ERenderCamera = {
	create: ERenderCamera_create,
	renderScene: ERenderCamera_renderScene,
	setSize: ERenderCamera_setSize,
};