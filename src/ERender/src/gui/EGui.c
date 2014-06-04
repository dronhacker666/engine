#include <gui/EGui.h>
#include <libfont.h>
#include <render/ERenderOpenGL.h>

void EGui_initEvents(EGuiManager_p);

EGuiManager_p EGui_create(void)
{
	Libfont.init();

	EGuiManager_p manager = EMem.alloc(sizeof(EGuiManager));

	manager->events = EEvents.create();
	EGui_initEvents(manager);

	static float block[] = {
		0.0f,1.0f,
		1.0f,1.0f,
		0.0f,0.0f,
		1.0f,1.0f,
		1.0f,0.0f,
		0.0f,0.0f
	};

	glGenVertexArrays(1, &manager->block_VAO);
	glBindVertexArray(manager->block_VAO);

	glGenBuffers(1, &manager->block_VBO);
	glBindBuffer(GL_ARRAY_BUFFER, manager->block_VBO);
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
			color = texture(iTex0, fragTexcoord);\n\
		}\n\
	";
	manager->shaderManager->fragmentShader = ERenderShader.create(fragment_src, sizeof(fragment_src), GL_FRAGMENT_SHADER);


	ERenderShaderManager.prepareShaders(manager->shaderManager);

	glBindBuffer(GL_ARRAY_BUFFER, manager->block_VBO);
	GLint positionLocation = glGetAttribLocation(manager->shaderManager->shader_id, "iPosition");
	if(positionLocation !=-1 ){
		glVertexAttribPointer(positionLocation, 2, GL_FLOAT, GL_FALSE, 2*sizeof(float), 0);
		glEnableVertexAttribArray(positionLocation);
	}

	return manager;
}

void EGui_onKeyPress(KeyboardEvent_p event, EGuiManager_p manager)
{
	printf("%i\n", event->keyCode);
}

void EGui_initEvents(EGuiManager_p manager)
{
	EEvents.addListener(manager->events, keyPress, (void*)EGui_onKeyPress, manager);
	//EEvents.addListener(manager->events, keyDown, (void*)onKeyPress);
	//EEvents.addListener(manager->events, keyUp, (void*)onKeyPress);
	//EEvents.addListener(manager->events, mouseDown, (void*)onKeyPress);
	//EEvents.addListener(manager->events, mouseUp, (void*)onKeyPress);
	//EEvents.addListener(manager->events, mouseMove, (void*)onKeyPress);
}

void EGui_addItem(EGuiManager_p manager, EGuiItem_p item)
{

	glGenTextures(1, &item->texture);
	glBindTexture(GL_TEXTURE_2D, item->texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

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

	glBindVertexArray(manager->block_VAO);

	glActiveTexture(GL_TEXTURE0);
	glUniform1i(glGetUniformLocation(manager->shaderManager->shader_id, "iTex0") , 0);

	GLuint box_pos = glGetUniformLocation(manager->shaderManager->shader_id, "box.pos");
	GLuint box_size = glGetUniformLocation(manager->shaderManager->shader_id, "box.size");

	glClear(GL_DEPTH_BUFFER_BIT);

	EGuiItem_p item = manager->_head;
	while(item){
		if(item->buffer){

			glUniform2f(box_pos, item->x, item->y);
			glUniform2f(box_size, item->width, item->height);
			glBindTexture(GL_TEXTURE_2D, item->texture);

			if(item->hasChanged){
				glTexImage2D(
					GL_TEXTURE_2D,
					0,
					GL_RGBA8,
					item->width,
					item->height,
					0,
					GL_RGBA,
					GL_UNSIGNED_BYTE,
					item->buffer
				);
				item->hasChanged = false;
			}

			glDrawArrays(GL_TRIANGLES, 0, 6);
		}
		item = item->_next;
	}
}


_EGui EGui = {
	create: EGui_create,
	render: EGui_render,
	addItem: EGui_addItem,
};
