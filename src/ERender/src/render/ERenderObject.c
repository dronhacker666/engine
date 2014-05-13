#include "ERenderObject.h"
#include "ERenderOpenGL.h"
#include "ERenderTexture.h"

ERenderObjectInstance_p ERenderObject_load(const char* filename)
{
	ERenderObjectInstance_p object = EMem.alloc(sizeof(ERenderObjectInstance));
	Model_p model = ModelLoader.loadOBJ(filename);

	object->_sys.vertexCount = model->vertexCount;

	glGenVertexArrays(1, &object->_sys.VAO);
	glBindVertexArray(object->_sys.VAO);

	glGenBuffers(1, &object->_sys.VBO);
	glBindBuffer(GL_ARRAY_BUFFER, object->_sys.VBO);
	glBufferData(GL_ARRAY_BUFFER, model->vertexCount * sizeof(float) * 8, model->mesh, GL_STATIC_DRAW);

	return object;
}

BOOL ERenderObject_loadTexture(ERenderObjectInstance_p object, char* filename, int index)
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
	load: ERenderObject_load,
	loadTexture: ERenderObject_loadTexture,
};