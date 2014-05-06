#include "ERender.h"
#include "ERenderOpenGL.h"

ERenderInstance_p ERenderCreate(int width, int height){

	new(render, ERenderInstance);

	render->width = width;
	render->height = height;

	render->events = EEvents.create();

	if( !ERenderOGLInit(render) ){
		return FALSE;
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
	RenderEvent event_beforeRender = {type: beforeRender};
	RenderEvent event_afterRender = {type: afterRender};

	EEvents.addEvent(render->events, &event_beforeRender);
	ERenderCamera.renderScene(render->camera, render->scene);
	EEvents.addEvent(render->events, &event_afterRender);
}


_ERender ERender = {
	create: 		ERenderCreate,
	render: 		ERenderRender,
	setScene: 		ERenderSetScene,
};