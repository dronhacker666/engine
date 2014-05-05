#include "ERenderObject.h"
#include "ERenderOpenGL.h"
#include "ERenderTexture.h"

ERenderObjectInstance_p ERenderObjectCreateFromMesh(MeshData_p data)
{
	ERenderObjectInstance_p object = malloc(sizeof(ERenderObjectInstance));

	glGenVertexArrays(1, &object->_sys.VAO);
	glBindVertexArray(object->_sys.VAO);

	glGenBuffers(1, &object->_sys.positionVBO);
	glBindBuffer(GL_ARRAY_BUFFER, object->_sys.positionVBO);
	glBufferData(GL_ARRAY_BUFFER, data->position.length * 3 * sizeof(float), data->position.data, GL_STATIC_DRAW);

	glGenBuffers(1, &object->_sys.texcoordVBO);
	glBindBuffer(GL_ARRAY_BUFFER, object->_sys.texcoordVBO);
	glBufferData(GL_ARRAY_BUFFER, data->texcoord.length * 2 * sizeof(float), data->texcoord.data, GL_STATIC_DRAW);

	object->_sys.countIndexes = data->index.length;
	glGenBuffers(1, &object->_sys.indexVBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, object->_sys.indexVBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, data->index.length * sizeof(uint32_t), data->index.data, GL_STATIC_DRAW);

	object->pos.x = 0;
	object->pos.y = 0;
	object->pos.z = 0;
	object->pos.rx = 0;
	object->pos.ry = 0;
	object->pos.rz = 0;

	return object;
}

ERenderObjectInstance_p ERenderObjectLoad(char* filename)
{

}

BOOL ERenderObjectLoadTexture(ERenderObjectInstance_p object, char* filename, int index)
{
	GLuint texture = ERenderTexture.load(filename);
	if(!texture){
		return FALSE;
	}
	switch(index){
		case 0: object->texture0 = texture; break;
		case 1: object->texture1 = texture; break;
		case 2: object->texture2 = texture; break;

		//default: // error
	}
	return TRUE;
}


_ERenderObject ERenderObject = {
	createFromMesh: ERenderObjectCreateFromMesh,
	loadTexture: ERenderObjectLoadTexture,
};