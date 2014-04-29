#include "../include/ERender.h"
#include "ERenderOpenGL.h"

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

	glClearColor(0.8, 0.8, 0.8, 0.0);
	glShadeModel(GL_FLAT);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glColor3f(0.0, 0.0, 0.0);

	glBegin(GL_LINES);
	glVertex3f(100.0f, 100.0f, 0.0f);
	glVertex3f(200.0f, 140.0f, 5.0f);
	glEnd( );

	glBegin(GL_TRIANGLES);
	glVertex3f(10.0f, 10.0f, 0.0f);
	glVertex3f(15.0f, 10.0f, 0.0f);
	glVertex3f(12.0f, 5.0f, 0.0f);
	glEnd();

	SwapBuffers(gApi.hdc);
}


_ERender ERender = {
	create: ERenderCreate,
	render: ERenderRender,
	setScene: ERenderSetScene,
	createScene: ERenderCreateScene,
};