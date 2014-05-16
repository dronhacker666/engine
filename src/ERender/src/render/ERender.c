#include "ERender.h"

ERenderInstance_p ERenderCreate(const int width, const int height){

	ERenderInstance_p render = EMem.alloc(sizeof(ERenderInstance));

	render->width = width;
	render->height = height;

	render->events = EEvents.create();

	if( !ERenderOGLInit(render) ){
		return FALSE;
	}

	render->camera = ERenderCamera.create();
	render->camera->viewport.width = width;
	render->camera->viewport.height = height;

	render->scene = ERenderScene.create();

	return render;
}


void ERenderSetScene(const ERenderInstance_p render, const ERenderSceneInstance_p scene)
{
	render->scene = scene;
}


void ERenderRender(const ERenderInstance_p render)
{
	ERenderCamera.renderScene(render->camera, render->scene);
}


_ERender ERender = {
	create: 		ERenderCreate,
	render: 		ERenderRender,
	setScene: 		ERenderSetScene,
};