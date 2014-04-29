#include "../include/ERender.h"
#include "OpenGL.h"

GAPI gApi;
ERenderInstance render;

bool ERenderCreate(ERenderCreateOptions* options){
	if( !ERenderOGLInit(options, &gApi) ){
		return false;
	}

	render.viewport_x = 0;
	render.viewport_y = 0;
	render.viewport_width = options->width;
	render.viewport_height = options->height;

	return true;
}

EScene* ERenderCreateScene(void)
{
	return (EScene*)eArray.create(sizeof(int));
}

void ERenderSetScene(EScene* scene)
{
	render.scene = scene;
}

void ERenderRender(void)
{

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	SwapBuffers(gApi.hdc);

}


_ERender ERender = {
	create: ERenderCreate,
	render: ERenderRender,
	setScene: ERenderSetScene,
	createScene: ERenderCreateScene,
};