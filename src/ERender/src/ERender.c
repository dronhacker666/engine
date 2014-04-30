#include "ERender.h"
#include "ERenderOpenGL.h"

ERenderInstance_p ERenderCreate(ERenderCreateOptions_p options){

	ERenderInstance_p render = malloc(sizeof(ERenderInstance));

	if( !ERenderOGLInit(options, &render->gAPI) ){
		return false;
	}

	render->viewport_x = 0;
	render->viewport_y = 0;
	render->viewport_width = options->width;
	render->viewport_height = options->height;

	render->shaderManager = ERenderShaderManager.create();

	// TODO: create scene manager
	render->scene = malloc(sizeof(ERenderSceneInstance));
	render->scene->child = eArray.create(sizeof(ERenderObjectInstance_p));

	return render;
}


void ERenderSetScene(ERenderInstance_p render, ERenderSceneInstance_p scene)
{
	render->scene = scene;
}


void ERenderRenderObject(ERenderInstance_p render, ERenderObjectInstance_p object)
{
	ERenderShaderManager.prepareShaders(render->shaderManager);

	Matrix4f projectionMatrix;
	float aspectRatio = (float)800 / (float)600;
	ERenderMatrix.perspective4f(projectionMatrix, 45.0f, aspectRatio, 0.1f, 500.0f);

	GLint projectionMatrixLocation = glGetUniformLocation(render->shaderManager->shader_id, "projectionMatrix");

	glUniformMatrix4fv(projectionMatrixLocation, 1, GL_TRUE, projectionMatrix);

	GLint positionLocation = glGetAttribLocation(render->shaderManager->shader_id, "position");
	if (positionLocation != -1)
	{
		glVertexAttribPointer(positionLocation, 3, GL_FLOAT, GL_FALSE, 12, 0);
		glEnableVertexAttribArray(positionLocation);
	}

	glBindVertexArray(object->meshVAO);
	glBindBuffer(GL_ARRAY_BUFFER, object->meshVBO);
	glDrawArrays(GL_TRIANGLES, 0, 3);
}

void ERenderRender(ERenderInstance_p render)
{
	glClearColor(0.8, 0.8, 0.8, 0.0);
	glShadeModel(GL_FLAT);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	int i;
	for(i=0; i<render->scene->child->length; i++){
		ERenderRenderObject(render, (ERenderObjectInstance_p)*(void**)eArray.get(render->scene->child, i) );
	}

	SwapBuffers(render->gAPI.hdc);
}


_ERender ERender = {
	create: 		ERenderCreate,
	render: 		ERenderRender,
	renderObject: 	ERenderRenderObject,
	setScene: 		ERenderSetScene,
};