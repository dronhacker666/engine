#include "ERender.h"

ERenderInstance_p ERenderCreate(const int width, const int height){

	new(render, ERenderInstance);

	render->width = width;
	render->height = height;

	render->events = EEvents.create();

	if( !ERenderOGLInit(render) ){
		return FALSE;
	}

	render->camera = ERenderCamera.create();
	render->scene = ERenderScene.create();

	return render;
}


void ERenderSetScene(const ERenderInstance_p render, const ERenderSceneInstance_p scene)
{
	render->scene = scene;
}


void ERenderRender(const ERenderInstance_p render)
{
	RenderEvent event_beforeRender = {type: beforeRender, render: render};
	RenderEvent event_afterRender = {type: afterRender, render: render};

	EEvents.addEvent(render->events, &event_beforeRender);
	ERenderCamera.renderScene(render->camera, render->scene);
	EEvents.addEvent(render->events, &event_afterRender);
}


_ERender ERender = {
	create: 		ERenderCreate,
	render: 		ERenderRender,
	setScene: 		ERenderSetScene,
};