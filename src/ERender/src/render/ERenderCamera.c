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

	char vertex_src[] = "\
		#version 140\n\
		uniform mat4 viewMatrix;\n\
		uniform mat4 modelMatrix;\n\
		uniform vec3 cameraNormal;\n\
		in vec3 iPosition;\n\
		in vec2 iTexcoord;\n\
		in vec3 iNormal;\n\
		out vec2 fragTexcoord;\n\
		out vec3 fragNormal;\n\
		void main(void)\n\
		{\n\
			gl_Position = viewMatrix * (modelMatrix * vec4(iPosition, 1.0));\n\
			fragTexcoord = iTexcoord;\n\
			fragNormal = normalize(iNormal) - cameraNormal;\n\
		}\n\
	";
	camera->shaderManager->vertexShader = ERenderShader.create(vertex_src, sizeof(vertex_src), GL_VERTEX_SHADER);

	char fragment_src[] = "\
		#version 140\n\
		uniform int mtlID;\n\
		in vec2 fragTexcoord;\n\
		in vec3 fragNormal;\n\
		out vec4 oColor0;\n\
		out vec4 oColor1;\n\
		void main(void)\n\
		{\n\
			//color = texture(iTex0, fragTexcoord);\n\
			//oColor0 = texture(iTex0, fragTexcoord);\n\
			//oColor1.rgb = texture(iTex0, fragTexcoord).rgb * gl_FragCoord.w;\n\
			oColor1 = vec4(fragTexcoord, gl_FragCoord.w, mtlID);\n\
		}\n\
	";
	camera->shaderManager->fragmentShader = ERenderShader.create(fragment_src, sizeof(fragment_src), GL_FRAGMENT_SHADER);

	glBindFragDataLocation(camera->shaderManager->shader_id, 0, "oColor0");
	glBindFragDataLocation(camera->shaderManager->shader_id, 1, "oColor1");

	ERenderShaderManager.prepareShaders(camera->shaderManager);

	camera->position.z = -10;

	return camera;
}

void ERenderCamera_freeTextures(ERenderCameraInstance_p camera)
{
	if(camera->depth){
		glDeleteTextures(1, &camera->depth);
	}
	if(camera->color){
		glDeleteTextures(2, camera->color);
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

			camera->color[0] = TextureCreate(GL_RGBA16, GL_RGBA, width, height, NULL, false);
			glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, camera->color[0], 0);

			camera->color[1] = TextureCreate(GL_RGBA16F, GL_RGBA, width, height, NULL, false);
			glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT1, camera->color[1], 0);

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

	GLenum buffers[] = {GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1};
	glDrawBuffers(2, buffers);

	glDisable(GL_BLEND);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	ERenderCamera_render(camera, scene->models);

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glEnable(GL_BLEND);
}

_ERenderCamera ERenderCamera = {
	create: ERenderCamera_create,
	renderScene: ERenderCamera_renderScene,
	setSize: ERenderCamera_setSize,
};