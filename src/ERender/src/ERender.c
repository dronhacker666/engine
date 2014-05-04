#include "ERender.h"
#include "ERenderOpenGL.h"

ERenderInstance_p ERenderCreate(int width, int height){

	ERenderInstance_p render = malloc(sizeof(ERenderInstance));
	render->width = width;
	render->height = height;

	render->events = EEvents.create();

	if( !ERenderOGLInit(render) ){
		return false;
	}

	render->camera = ERenderCamera.create();

	// TODO: create scene manager
	render->scene = malloc(sizeof(ERenderSceneInstance));
	render->scene->child = eArray.create(sizeof(ERenderObjectInstance_p));

	return render;
}


void ERenderSetScene(ERenderInstance_p render, ERenderSceneInstance_p scene)
{
	render->scene = scene;
}


void ERenderRender(ERenderInstance_p render)
{
	EEvents.addEvent(render->events, beforeRender, render);
	ERenderCamera.renderScene(render->camera, render->scene);
	EEvents.addEvent(render->events, afterRender, render);
}


_ERender ERender = {
	create: 		ERenderCreate,
	render: 		ERenderRender,
	setScene: 		ERenderSetScene,
};