#include "EGui.h"

GLuint block_VBO, block_VAO;

EGuiManager_p EGui_create(void)
{
	new(manager, EGuiManager);

	const float width = 300;
	const float height = 120;

	float block[] = {
		 0.0,  0.0, 0.0,
		 0.0,  height, 0.0,
		 width,  height, 0.0,

		 0.0,  0.0, 0.0,
		 width,  height, 0.0,
		 width,  0.0, 0.0,
	};


	glGenVertexArrays(1, &block_VAO);
	glBindVertexArray(block_VAO);

	glGenBuffers(1, &block_VBO);
	glBindBuffer(GL_ARRAY_BUFFER, block_VBO);
	glBufferData(GL_ARRAY_BUFFER, 36 * sizeof(float), block, GL_STATIC_DRAW);



	manager->shaderManager = ERenderShaderManager.create();

	char vertex_src[] = "\
		#version 140\n\
		uniform vec2 resolution;\n\
		in vec3 iPosition;\n\
		void main(void)\n\
		{\n\
			vec3 pos = iPosition;\n\
			pos.x = pos.x/resolution.x - 1.0;\n\
			pos.y = 1.0 - pos.y/resolution.y;\n\
			gl_Position   =  vec4(pos, 1.0);\n\
		}\n\
	";
	manager->shaderManager->vertexShader = ERenderShader.create(vertex_src, sizeof(vertex_src), GL_VERTEX_SHADER);

	char fragment_src[] = "\
		#version 140\n\
		out vec4 color;\n\
		void main(void)\n\
		{\n\
			color = vec4(1.0, 1.0, 1.0, 1.0);\n\
		}\n\
	";
	manager->shaderManager->fragmentShader = ERenderShader.create(fragment_src, sizeof(fragment_src), GL_FRAGMENT_SHADER);


	return manager;
}

void EGui_addItem(EGuiManager_p manager, EGuiItem_p item)
{
	item->_next = NULL;
	item->_prev = manager->_current;

	if(manager->_head==NULL){
		manager->_head = item;
	}
	if(manager->_current!=NULL){
		manager->_current->_next = item;
	}
	manager->_current = item;
}


void EGui_render(EGuiManager_p manager)
{

	ERenderShaderManager.prepareShaders(manager->shaderManager);

	glUniform2f(glGetUniformLocation(manager->shaderManager->shader_id, "resolution"), 800, 600);

	glBindBuffer(GL_ARRAY_BUFFER, block_VBO);
	GLint positionLocation = glGetAttribLocation(manager->shaderManager->shader_id, "iPosition");
	if(positionLocation !=-1 ){
		glVertexAttribPointer(positionLocation, 3, GL_FLOAT, GL_FALSE, 3*sizeof(float), 0);
		glEnableVertexAttribArray(positionLocation);
	}


	glBindVertexArray(block_VAO);
	//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, NULL);
	glDrawArrays(GL_TRIANGLES, 0, 6);

	EGuiItem_p item = manager->_head;
	while(item){
		item->render(item);
		item = item->_next;
	}
}


_EGui EGui = {
	create: EGui_create,
	render: EGui_render,
	addItem: EGui_addItem,
};
