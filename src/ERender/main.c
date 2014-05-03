#include "include/ERenderAPI.h"
#include <windows.h>

ERenderInstance_p render;

int main(void)
{
	ERenderCreateOptions renderOptions = {
		width: 800,
		height: 600,
	};
	render = ERender.create(&renderOptions);


	// описание геометрии куба для всех его сторон
	// координаты вершин куба
	const float s = 1.0f; // половина размера куба
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

	while(!GetAsyncKeyState(VK_ESCAPE)){

		GetCursorPos(&mouse);


		if(GetAsyncKeyState(VK_UP)){ object1->pos.z+=0.1; }
		if(GetAsyncKeyState(VK_DOWN)){ object1->pos.z-=0.1; }
		if(GetAsyncKeyState(VK_LEFT)){ object1->pos.rz-=1; }
		if(GetAsyncKeyState(VK_RIGHT)){ object1->pos.rx-=1; }


		render->camera->pos.ry = mouse.x;
		render->camera->pos.rx = mouse.y;

		if(GetAsyncKeyState('W')){ render->camera->pos.z+=0.1; }
		if(GetAsyncKeyState('S')){ render->camera->pos.z-=0.1; }
		if(GetAsyncKeyState('A')){ render->camera->pos.x+=0.1; }
		if(GetAsyncKeyState('D')){ render->camera->pos.x-=0.1; }

		ERender.render(render);
	}

	return 0;
}