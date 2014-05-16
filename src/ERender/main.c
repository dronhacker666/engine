#include "include/ERenderAPI.h"
#include <windows.h>
#include <time.h>

ERenderInstance_p render;

void onKeyDown(KeyboardEvent_p event)
{
	printf("%i\n", event->keyCode );
}

void onBeforeRender(RenderEvent_p _event)
{

	if(EInput.keyPress('W')){
		render->camera->position.x -= sin(M_PI/180 * render->camera->rotation.y) / 100;
		render->camera->position.y += sin(M_PI/180 * render->camera->rotation.x) / 100;
		render->camera->position.z += cos(M_PI/180 * render->camera->rotation.y) / 100;
	}
	if(EInput.keyPress('S')){
		render->camera->position.x += sin(M_PI/180 * render->camera->rotation.y) / 100;
		render->camera->position.y -= sin(M_PI/180 * render->camera->rotation.x) / 100;
		render->camera->position.z -= cos(M_PI/180 * render->camera->rotation.y) / 100;
	}
	if(EInput.keyPress('D')){
		render->camera->position.x -= sin(M_PI/180 * (render->camera->rotation.y+90)) / 100;
		render->camera->position.y += sin(M_PI/180 * render->camera->rotation.x) / 100;
		render->camera->position.z += cos(M_PI/180 * (render->camera->rotation.y+90)) / 100;
	}
	if(EInput.keyPress('A')){
		render->camera->position.x -= sin(M_PI/180 * (render->camera->rotation.y-90)) / 100;
		render->camera->position.y += sin(M_PI/180 * render->camera->rotation.x) / 100;
		render->camera->position.z += cos(M_PI/180 * (render->camera->rotation.y-90)) / 100;
	}

}

void onMouseMove(MouseEvent_p _event)
{

}
void onMouseDown(MouseEvent_p _event)
{
	EEvents.addListener(render->events, mouseMove, (void*)onMouseMove);
}
void onMouseUp(MouseEvent_p _event)
{
	EEvents.removeListener(render->events, (void*)onMouseMove);
}

int main(void)
{
	render = ERender.create(800, 600);
	RenderEvent event_beforeRender = {type: beforeRender, render: render};
	RenderEvent event_afterRender = {type: afterRender, render: render};

	ERenderScene.load(render->scene, "../data/model.obj");
	ERenderObjectInstance_p beretta = ERenderScene.load(render->scene, "../data/beretta.obj");

	beretta->position.y = 4;


	EGuiManager_p gui = EGui.create();
	//EGuiButtonInstance_p button = EGuiButton.create();
	EGuiTextInstance_p text = EGuiText.create("Hello World!");
	EGui.addItem(gui, (EGuiItem_p)text);



	EInput.init();

	EEvents.addListener(render->events, keyDown, (void*)onKeyDown);
	EEvents.addListener(render->events, beforeRender, (void*)onBeforeRender);


	EEvents.addListener(render->events, mouseDown, (void*)onMouseDown);
	EEvents.addListener(render->events, mouseUp, (void*)onMouseUp);

	POINT mouse;

	int fps = 0;
	int s = 0;

	while(!GetAsyncKeyState(VK_ESCAPE)){

		GetCursorPos(&mouse);


		beretta->rotation.y += 0.1;

		render->camera->rotation.x = (float)mouse.y;
		render->camera->rotation.y = (float)mouse.x;

		EEvents.addEvent(render->events, &event_beforeRender);

		ERender.render(render);
		EGui.render(gui);

		EEvents.addEvent(render->events, &event_afterRender);

		fps++;
		if(clock()-s>1000){
			printf("fps: %i\n", fps);
			s = clock();
			fps = 0;
		}
	}


	EMem.printUsage();

	return 0;
}