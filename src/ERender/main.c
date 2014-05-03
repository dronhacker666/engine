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

	// количество вершин в нашей геометрии, у нас простой треугольник
	const int vertexCount = 3;

	// размер одной вершины меша в байтах - 6 float на позицию и на цвет вершины
	const int vertexSize = 3 * sizeof(float);
	float triangleMesh[9] = {
		-1.0f, -1.0f, -2.0f,
		 0.0f,  1.0f, -2.0f,
		 1.0f, -1.0f, -2.0f
	};

	ERenderObjectInstance_p object1 = ERenderObject.createFromMesh(triangleMesh, vertexCount*vertexSize);
	ERenderObjectInstance_p object2 = ERenderObject.createFromMesh(triangleMesh, vertexCount*vertexSize);
	ERenderObjectInstance_p object3 = ERenderObject.createFromMesh(triangleMesh, vertexCount*vertexSize);
	ERenderObjectInstance_p object4 = ERenderObject.createFromMesh(triangleMesh, vertexCount*vertexSize);

	eArray.push(render->scene->child, &object1);
	eArray.push(render->scene->child, &object2);
	eArray.push(render->scene->child, &object3);
	eArray.push(render->scene->child, &object4);


	object1->pos.x = 10;
	object2->pos.x = 5;
	object3->pos.x = -5;
	object4->pos.x = -10;


	POINT mouse;

	while(!GetAsyncKeyState(VK_ESCAPE)){

		GetCursorPos(&mouse);

		render->camera->pos.ry = -mouse.x;
		render->camera->pos.rx = -mouse.y;

		if(GetAsyncKeyState('W')){ render->camera->pos.z-=0.05; }
		if(GetAsyncKeyState('S')){ render->camera->pos.z+=0.05; }
		if(GetAsyncKeyState('A')){ render->camera->pos.x+=0.05; }
		if(GetAsyncKeyState('D')){ render->camera->pos.x-=0.05; }

		ERender.render(render);
	}

	return 0;
}