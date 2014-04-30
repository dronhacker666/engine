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

	ERenderObjectInstance_p object = ERenderObject.createFromMesh(triangleMesh, vertexCount*vertexSize);

	eArray.push(render->scene->child, &object);

	while(!GetAsyncKeyState(VK_ESCAPE)){


		ERender.render(render);
	}

	return 0;
}