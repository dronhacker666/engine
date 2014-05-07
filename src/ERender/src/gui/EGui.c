#include "EGui.h"

GLuint block_VBO, block_VAO;

EGuiManager_p EGui_create(void)
{
	new(manager, EGuiManager);

	float block[] = {
		 0.0,  0.0,
		 0.0,  2.0,
		 2.0,  2.0,
		 0.0,  0.0,
		 2.0,  2.0,
		 2.0,  0.0,
	};


	glGenVertexArrays(1, &block_VAO);
	glBindVertexArray(block_VAO);

	glGenBuffers(1, &block_VBO);
	glBindBuffer(GL_ARRAY_BUFFER, block_VBO);
	glBufferData(GL_ARRAY_BUFFER, 12 * sizeof(float), block, GL_STATIC_DRAW);



	manager->shaderManager = ERenderShaderManager.create();

	char vertex_src[] = "\
		#version 140\n\
		struct Box {\n\
			vec2 pos;\n\
			vec2 size;\n\
			float zIndex;\n\
		};\n\
		uniform Box box;\n\
		uniform vec2 resolution;\n\
		in vec2 iPosition;\n\
		void main(void)\n\
		{\n\
			vec2 res;\n\
			res.x = (box.pos.x + iPosition.x*box.size.x)/resolution.x - 1.0;\n\
			res.y = 1.0 - (box.pos.y + iPosition.y*box.size.y)/resolution.y;\n\
			gl_Position = vec4(res, box.zIndex, 1.0);\n\
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


	ERenderShaderManager.prepareShaders(manager->shaderManager);

	glBindBuffer(GL_ARRAY_BUFFER, block_VBO);
	GLint positionLocation = glGetAttribLocation(manager->shaderManager->shader_id, "iPosition");
	if(positionLocation !=-1 ){
		glVertexAttribPointer(positionLocation, 2, GL_FLOAT, GL_FALSE, 2*sizeof(float), 0);
		glEnableVertexAttribArray(positionLocation);
	}

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

	glUniform2f(glGetUniformLocation(manager->shaderManager->shader_id, "box.pos"), 100, 100);
	glUniform2f(glGetUniformLocation(manager->shaderManager->shader_id, "box.size"), 100, 22);
	glUniform1f(glGetUniformLocation(manager->shaderManager->shader_id, "box.zIndex"), 0);

	glBindVertexArray(block_VAO);
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
