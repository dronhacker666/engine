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
	if(EInput.keyPress('W')){ render->camera->pos.z+=0.01; }
	if(EInput.keyPress('S')){ render->camera->pos.z-=0.01; }
	if(EInput.keyPress('A')){ render->camera->pos.x+=0.01; }
	if(EInput.keyPress('D')){ render->camera->pos.x-=0.01; }
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


	EGuiManager_p gui = EGui.create();
	EGuiButtonInstance_p button = EGuiButton.create();
	EGui.addItem(gui, (EGuiItem_p)button);
	//EGui.render(gui);
	//SwapBuffers(render->gAPI.hdc);
	//while(!GetAsyncKeyState(VK_ESCAPE)){}


	EInput.init();

	EEvents.addListener(render->events, keyDown, (void*)onKeyDown);
	EEvents.addListener(render->events, beforeRender, (void*)onBeforeRender);


	EEvents.addListener(render->events, mouseDown, (void*)onMouseDown);
	EEvents.addListener(render->events, mouseUp, (void*)onMouseUp);


	ERenderObjectInstance_p object1 = ERenderObject.load("../data/beretta.obj");
	ERenderScene.addObject(render->scene, object1);

	ERenderObject.loadTexture(object1, "../data/beretta.jpg", 0);

	POINT mouse;

	int fps = 0;
	int s = 0;

	RenderEvent event_beforeRender = {type: beforeRender, render: render};
	RenderEvent event_afterRender = {type: afterRender, render: render};

	while(!GetAsyncKeyState(VK_ESCAPE)){

		GetCursorPos(&mouse);

		render->camera->pos.rx = (float)mouse.y/1000;
		render->camera->pos.ry = (float)mouse.x/1000;

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