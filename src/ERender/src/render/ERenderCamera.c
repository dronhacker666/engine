#include <render/ERenderCamera.h>
#include <render/ERenderOpenGL.h>
#include <render/ERenderModel.h>
#include <render/ERenderGroup.h>

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
		uniform sampler2D iTex0;\n\
		uniform int iMeshId;\n\
		in vec2 fragTexcoord;\n\
		in vec3 fragNormal;\n\
		out vec4 oColor0;\n\
		out vec4 oColor1;\n\
		void main(void)\n\
		{\n\
			oColor0 = vec4(texture(iTex0, fragTexcoord).rgb, gl_FragCoord.w);\n\
			oColor1 = vec4(iMeshId, 1.0, 1.0, 1.0);\n\
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

			camera->color[0] = TextureCreate(GL_RGBA8, GL_RGBA, width, height, NULL, false);
			glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, camera->color[0], 0);

			camera->color[1] = TextureCreate(GL_RGBA8, GL_RGBA, width, height, NULL, false);
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


void ERenderCamera_renderModel(ERenderCameraInstance_p camera, ERenderModelInstance_p model)
{
	Matrix4f 
		translationModel,
		rotationModel,
		modelMatrix;

	Vec3f cameraNormal;
	Vec.direction3f(&cameraNormal, &camera->position, &model->position);
	glUniform3fv(glGetUniformLocation(camera->shaderManager->shader_id, "cameraNormal"), 1, (const GLfloat*)&cameraNormal);

	ERenderMatrix.translation4f(translationModel, model->position.x, model->position.y, model->position.z);
	ERenderMatrix.rotation4f(rotationModel, model->rotation.x, model->rotation.y, model->rotation.z);
	ERenderMatrix.mul4f(modelMatrix, translationModel, rotationModel);
	glUniformMatrix4fv(glGetUniformLocation(camera->shaderManager->shader_id, "modelMatrix"), 1, GL_TRUE, modelMatrix);


	glUniform1i(glGetUniformLocation(camera->shaderManager->shader_id, "iMeshId"), model->_id);


	glBindVertexArray(model->VAO);
	glBindBuffer(GL_ARRAY_BUFFER, model->VBO);

	GLint positionLocation = glGetAttribLocation(camera->shaderManager->shader_id, "iPosition");
	GLint texcoordLocation = glGetAttribLocation(camera->shaderManager->shader_id, "iTexcoord");
	GLint normalLocation = glGetAttribLocation(camera->shaderManager->shader_id, "iNormal");

	glVertexAttribPointer(positionLocation, 3, GL_FLOAT, GL_FALSE, 8*sizeof(float), 0);
	glEnableVertexAttribArray(positionLocation);

	glVertexAttribPointer(texcoordLocation, 2, GL_FLOAT, GL_FALSE, 8*sizeof(float), (const GLvoid*)(sizeof(float)*3) );
	glEnableVertexAttribArray(texcoordLocation);

	glVertexAttribPointer(normalLocation, 3, GL_FLOAT, GL_FALSE, 8*sizeof(float), (const GLvoid*)(sizeof(float)*5) );
	glEnableVertexAttribArray(normalLocation);

	// Textures

	if(model->mtl){
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, model->mtl->tex[0]);
	}

	glDrawArrays(GL_TRIANGLES, 0, model->vertexCount);
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
				ERenderCamera_renderModel(camera, (ERenderModelInstance_p)object);
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