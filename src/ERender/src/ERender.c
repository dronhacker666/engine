#include "../include/ERender.h"
#include "OpenGL.h"

ERenderInstance render;

bool ERenderCreate(ERenderCreateOptions* options){
	if( ERenderOGLInit(options) ){
		render.viewport_x = 0;
		render.viewport_y = 0;
		render.viewport_width = options->width;
		render.viewport_height = options->height;
		return true;
	}else{
		return false;
	}
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

}


_ERender ERender = {
	create: ERenderCreate,
	render: ERenderRender,
	setScene: ERenderSetScene,
	createScene: ERenderCreateScene,
};