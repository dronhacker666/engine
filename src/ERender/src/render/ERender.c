#include "ERender.h"
#include "ERenderOpenGL.h"

void ERender_initRenderRect(void);

ERenderInstance_p ERenderCreate(const int width, const int height){

	ERenderInstance_p render = EMem.alloc(sizeof(ERenderInstance));

	render->width = width;
	render->height = height;

	render->events = EEvents.create();

	if( !ERenderOGLInit(render) ){
		return FALSE;
	}

	render->camera = ERenderCamera.create();
	ERenderCamera.setSize(render->camera, width, height);

	render->scene = ERenderScene.create();

	ERender_initRenderRect();

	return render;
}

GLuint block_VBO123, block_VAO123;
ERenderShaderManagerInstance_p shaderManager;
void ERender_initRenderRect(void)
{
	const float block123[] = {
		-1.0f, -1.0f,  0.0f,0.0f,
		 1.0f, -1.0f,  1.0f,0.0f,
		-1.0f,  1.0f,  0.0f,1.0f,
		 1.0f, -1.0f,  1.0f,0.0f,
		 1.0f,  1.0f,  1.0f,1.0f,
		-1.0f,  1.0f,  0.0f,1.0f
	};

	glGenVertexArrays(1, &block_VAO123);
	glBindVertexArray(block_VAO123);

	glGenBuffers(1, &block_VBO123);
	glBindBuffer(GL_ARRAY_BUFFER, block_VBO123);
	glBufferData(GL_ARRAY_BUFFER, 6 * 4 * sizeof(float), block123, GL_STATIC_DRAW);

	shaderManager = ERenderShaderManager.create();

	char vertex_src[] = "\
		#version 140\n\
		in vec2 iPosition;\n\
		in vec2 iTexcoord;\n\
		out vec2 fragTexcoord;\n\
		void main(void)\n\
		{\n\
			fragTexcoord  = iTexcoord;\n\
			gl_Position = vec4(iPosition, 0.0, 1.0);\n\
		}\n\
	";
	shaderManager->vertexShader = ERenderShader.create(vertex_src, sizeof(vertex_src), GL_VERTEX_SHADER);

	char fragment_src[] = "\
		#version 140\n\
		uniform sampler2D iTex0;\n\
		uniform sampler2D iTex1;\n\
		uniform sampler2D iTex2;\n\
		uniform sampler2D iTex3;\n\
		in vec2 fragTexcoord;\n\
		out vec4 color;\n\
		void main(void)\n\
		{\n\
			vec4 data = texture(iTex0, fragTexcoord);\n\
			vec3 _color = data.rgb;\n\
			float _depth = data.a;\n\
			color = vec4(_color, 1.0);\n\
		}\n\
	";
	shaderManager->fragmentShader = ERenderShader.create(fragment_src, sizeof(fragment_src), GL_FRAGMENT_SHADER);

	ERenderShaderManager.prepareShaders(shaderManager);

	glUniform1i(glGetUniformLocation(shaderManager->shader_id, "iTex0") , 0);

	glUniform1i(glGetUniformLocation(shaderManager->shader_id, "iTex1") , 1);
	glUniform1i(glGetUniformLocation(shaderManager->shader_id, "iTex2") , 2);
	glUniform1i(glGetUniformLocation(shaderManager->shader_id, "iTex3") , 3);

	glBindBuffer(GL_ARRAY_BUFFER, block_VBO123);
	GLint positionLocation = glGetAttribLocation(shaderManager->shader_id, "iPosition");;
	glVertexAttribPointer(positionLocation, 2, GL_FLOAT, GL_FALSE, 4*sizeof(float), 0);
	glEnableVertexAttribArray(positionLocation);

	GLint texcoordLocation = glGetAttribLocation(shaderManager->shader_id, "iTexcoord");;
	glVertexAttribPointer(texcoordLocation, 2, GL_FLOAT, GL_FALSE, 4*sizeof(float), (const GLvoid*)(sizeof(float)*2) );
	glEnableVertexAttribArray(texcoordLocation);
}

void ERender_renderRect(ERenderInstance_p render, int x, int y, int width, int height, GLint texture)
{
	ERenderShaderManager.prepareShaders(shaderManager);

	glBindVertexArray(block_VAO123);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);

	glDrawArrays(GL_TRIANGLES, 0, 6);
}



void ERenderSetScene(const ERenderInstance_p render, const ERenderSceneInstance_p scene)
{
	render->scene = scene;
}


void ERenderRender(const ERenderInstance_p render)
{
	ERenderCamera.renderScene(render->camera, render->scene);

	ERender_renderRect(render, 0, 0, render->width, render->height, render->camera->color[1]);
}


_ERender ERender = {
	create: 		ERenderCreate,
	render: 		ERenderRender,
	setScene: 		ERenderSetScene,
};