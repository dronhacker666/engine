#include <gui/EGui.h>

GLuint block_VBO, block_VAO;

EGuiManager_p EGui_create(void)
{
	EGuiManager_p manager = EMem.alloc(sizeof(EGuiManager));

	static float block[] = {
		0.0f,1.0f,
		1.0f,1.0f,
		0.0f,0.0f,
		1.0f,1.0f,
		1.0f,0.0f,
		0.0f,0.0f
	};

	glGenVertexArrays(1, &block_VAO);
	glBindVertexArray(block_VAO);

	glGenBuffers(1, &block_VBO);
	glBindBuffer(GL_ARRAY_BUFFER, block_VBO);
	glBufferData(GL_ARRAY_BUFFER, 6 * 2 * sizeof(float), block, GL_STATIC_DRAW);

	manager->shaderManager = ERenderShaderManager.create();

	char vertex_src[] = "\
		#version 140\n\
		struct Box {\n\
			vec2 pos;\n\
			vec2 size;\n\
		};\n\
		uniform Box box;\n\
		uniform vec2 resolution;\n\
		in vec2 iPosition;\n\
		out vec2 fragTexcoord;\n\
		void main(void)\n\
		{\n\
			vec2 res;\n\
			res.x = (iPosition.x*2.0*box.size.x + box.pos.x)/resolution.x - 1.0;\n\
			res.y = 1.0 - (iPosition.y*2.0*box.size.y + box.pos.y)/resolution.y;\n\
			gl_Position = vec4(res, 0.0, 1.0);\n\
			fragTexcoord  = iPosition;\n\
		}\n\
	";
	manager->shaderManager->vertexShader = ERenderShader.create(vertex_src, sizeof(vertex_src), GL_VERTEX_SHADER);

	char fragment_src[] = "\
		#version 140\n\
		uniform sampler2D iTex0;\n\
		in vec2 fragTexcoord;\n\
		out vec4 color;\n\
		void main(void)\n\
		{\n\
			color = vec4(1.0, 1.0, 1.0, max(0.2, texture(iTex0, fragTexcoord).r) );\n\
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

	glUniform2f(glGetUniformLocation(manager->shaderManager->shader_id, "box.pos"), 10, 10);
	glUniform2f(glGetUniformLocation(manager->shaderManager->shader_id, "box.size"), 200, 100);

	glBindVertexArray(block_VAO);

	glClear(GL_DEPTH_BUFFER_BIT);

	EGuiItem_p item = manager->_head;
	while(item){

		item->render(item, manager);
		glDrawArrays(GL_TRIANGLES, 0, 6);
		item = item->_next;
	}
}


_EGui EGui = {
	create: EGui_create,
	render: EGui_render,
	addItem: EGui_addItem,
};
