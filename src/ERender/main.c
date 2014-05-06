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
	EGuiTextInstance_p text = EGuiText.create("Hello World");
	EGuiButtonInstance_p button = EGuiButton.create();
	EGui.addItem(gui, (EGuiItem_p)text);
	EGui.addItem(gui, (EGuiItem_p)button);

	EGui.render(gui);

	SwapBuffers(render->gAPI.hdc);

	while(!GetAsyncKeyState(VK_ESCAPE)){}



	EInput.init();

	EEvents.addListener(render->events, keyDown, (void*)onKeyDown);
	EEvents.addListener(render->events, beforeRender, (void*)onBeforeRender);


	EEvents.addListener(render->events, mouseDown, (void*)onMouseDown);
	EEvents.addListener(render->events, mouseUp, (void*)onMouseUp);


	// описание геометрии куба для всех его сторон
	// координаты вершин куба
	const float cubePositions[24][3] = {
		{-1.0f, 1.0f, 1.0f}, { 1.0f, 1.0f, 1.0f}, { 1.0f,-1.0f, 1.0f}, {-1.0f,-1.0f, 1.0f}, // front
		{ 1.0f, 1.0f,-1.0f}, {-1.0f, 1.0f,-1.0f}, {-1.0f,-1.0f,-1.0f}, { 1.0f,-1.0f,-1.0f}, // back
		{-1.0f, 1.0f,-1.0f}, { 1.0f, 1.0f,-1.0f}, { 1.0f, 1.0f, 1.0f}, {-1.0f, 1.0f, 1.0f}, // top
		{ 1.0f,-1.0f,-1.0f}, {-1.0f,-1.0f,-1.0f}, {-1.0f,-1.0f, 1.0f}, { 1.0f,-1.0f, 1.0f}, // bottom
		{-1.0f, 1.0f,-1.0f}, {-1.0f, 1.0f, 1.0f}, {-1.0f,-1.0f, 1.0f}, {-1.0f,-1.0f,-1.0f}, // left
		{ 1.0f, 1.0f, 1.0f}, { 1.0f, 1.0f,-1.0f}, { 1.0f,-1.0f,-1.0f}, { 1.0f,-1.0f, 1.0f}  // right
	};

	// текстурные координаты куба
	const float cubeTexcoords[24][2] = {
		{0.0f,1.0f}, {1.0f,1.0f}, {1.0f,0.0f}, {0.0f,0.0f}, // front
		{0.0f,1.0f}, {1.0f,1.0f}, {1.0f,0.0f}, {0.0f,0.0f}, // back
		{0.0f,1.0f}, {1.0f,1.0f}, {1.0f,0.0f}, {0.0f,0.0f}, // top
		{0.0f,1.0f}, {1.0f,1.0f}, {1.0f,0.0f}, {0.0f,0.0f}, // bottom
		{0.0f,1.0f}, {1.0f,1.0f}, {1.0f,0.0f}, {0.0f,0.0f}, // left
		{0.0f,1.0f}, {1.0f,1.0f}, {1.0f,0.0f}, {0.0f,0.0f}  // right
	};

	// индексы вершин куба в порядке поротив часовой стрелки
	const uint32_t cubeIndices[36] = {
			 0, 3, 1,  1, 3, 2, // front
			 4, 7, 5,  5, 7, 6, // back
			 8,11, 9,  9,11,10, // top
			12,15,13, 13,15,14, // bottom
			16,19,17, 17,19,18, // left
			20,23,21, 21,23,22  // right
	};

	MeshData mesh = {
		position:{
			data: cubePositions,
			length: 24
		},
		texcoord:{
			data: cubeTexcoords,
			length: 24
		},
		index:{
			data: cubeIndices,
			length: 36
		},
	};


	ERenderObjectInstance_p object1 = ERenderObject.createFromMesh(&mesh);
	eArray.push(render->scene->child, &object1);

	ERenderObject.loadTexture(object1, "../data/texture.tga", 0);

	POINT mouse;

	int fps = 0;
	int s = 0;

	while(!GetAsyncKeyState(VK_ESCAPE)){

		GetCursorPos(&mouse);

		render->camera->pos.rx = (float)mouse.y/1000;
		render->camera->pos.ry = (float)mouse.x/1000;

		ERender.render(render);

		fps++;
		if(clock()-s>1000){
			printf("fps: %i\n", fps);
			s = clock();
			fps = 0;
		}



	}

	return 0;
}