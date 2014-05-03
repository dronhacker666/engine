#include "ERender.h"
#include "ERenderOpenGL.h"

ERenderInstance_p ERenderCreate(ERenderCreateOptions_p options){

	ERenderInstance_p render = malloc(sizeof(ERenderInstance));

	if( !ERenderOGLInit(options, &render->gAPI) ){
		return false;
	}

	// TODO: create scene manager
	render->scene = malloc(sizeof(ERenderSceneInstance));
	render->scene->child = eArray.create(sizeof(ERenderObjectInstance_p));

	render->camera = ERenderCamera.create();

	return render;
}


void ERenderSetScene(ERenderInstance_p render, ERenderSceneInstance_p scene)
{
	render->scene = scene;
}


void ERenderRender(ERenderInstance_p render)
{
	ERenderCamera.renderScene(render->camera, render->scene);

	SwapBuffers(render->gAPI.hdc);
}


_ERender ERender = {
	create: 		ERenderCreate,
	render: 		ERenderRender,
	setScene: 		ERenderSetScene,
};