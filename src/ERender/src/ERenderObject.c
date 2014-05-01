#include "ERenderObject.h"
#include "ERenderOpenGL.h"

ERenderObjectInstance_p ERenderObjectCreateFromMesh(CRenderMesh mesh, unsigned int length)
{
	ERenderObjectInstance_p object = malloc(sizeof(ERenderObjectInstance));

	glGenVertexArrays(1, &object->meshVAO);
	glBindVertexArray(object->meshVAO);

	glGenBuffers(1, &object->meshVBO);
	glBindBuffer(GL_ARRAY_BUFFER, object->meshVBO);

	glBufferData(GL_ARRAY_BUFFER, length, mesh, GL_STATIC_DRAW);

	return object;
}


_ERenderObject ERenderObject = {
	createFromMesh: ERenderObjectCreateFromMesh,
};