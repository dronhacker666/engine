#include <render/ERender.h>
#include <input/EInput.h>
#include <render/ERenderOpenGL.h>

void ERender_initRenderRect(ERenderInstance_p);
void ERender_initEvents(ERenderInstance_p);

ERenderInstance_p ERenderCreate(const int width, const int height){

	ERenderInstance_p render = EMem.alloc(sizeof(ERenderInstance));
	render->width = width;
	render->height = height;

	render->events = EEvents.create();
	EInput.init(render->events);

	if( !ERenderOGLInit(render) ){
		return false;
	}

	render->gui = EGui.create();
	render->gui->screen_width = width;
	render->gui->screen_height = height;

	render->camera = ERenderCamera.create();
	ERenderCamera.setSize(render->camera, width, height);

	render->scene = ERenderScene.create();

	ERender_initRenderRect(render);
	ERender_initEvents(render);

	render->enabled = true;

	return render;
}


void ERender_proxyEventToGui(void* event, ERenderInstance_p render)
{
	EEvents.addEvent(render->gui->events, event);
}

void ERender_initEvents(ERenderInstance_p render)
{
	EEvents.addListener(render->events, keyPress, 	(void*)ERender_proxyEventToGui, render);
	EEvents.addListener(render->events, keyDown, 	(void*)ERender_proxyEventToGui, render);
	EEvents.addListener(render->events, keyUp, 		(void*)ERender_proxyEventToGui, render);
	EEvents.addListener(render->events, mouseDown, 	(void*)ERender_proxyEventToGui, render);
	EEvents.addListener(render->events, mouseUp, 	(void*)ERender_proxyEventToGui, render);
	EEvents.addListener(render->events, mouseMove, 	(void*)ERender_proxyEventToGui, render);
}

void ERender_initRenderRect(ERenderInstance_p render)
{
	const float block[] = {
		-1.0f, -1.0f,  0.0f,0.0f,
		 1.0f, -1.0f,  1.0f,0.0f,
		-1.0f,  1.0f,  0.0f,1.0f,
		 1.0f, -1.0f,  1.0f,0.0f,
		 1.0f,  1.0f,  1.0f,1.0f,
		-1.0f,  1.0f,  0.0f,1.0f
	};

	glGenVertexArrays(1, &render->block_VAO);
	glBindVertexArray(render->block_VAO);

	glGenBuffers(1, &render->block_VBO);
	glBindBuffer(GL_ARRAY_BUFFER, render->block_VBO);
	glBufferData(GL_ARRAY_BUFFER, 6 * 4 * sizeof(float), block, GL_STATIC_DRAW);

	render->shaderManager = ERenderShaderManager.create();

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
	render->shaderManager->vertexShader = ERenderShader.create(vertex_src, sizeof(vertex_src), GL_VERTEX_SHADER);

	char fragment_src[] = "\
		#version 140\n\
		uniform vec2 iResolution;\n\
		uniform sampler2D iTex0;\n\
		uniform sampler2D iTex1;\n\
		uniform sampler2D iTex2;\n\
		uniform sampler2D iTex3;\n\
		in vec2 fragTexcoord;\n\
		out vec4 color;\n\
		void main(void)\n\
		{\n\
			float x = iResolution.x * fragTexcoord.x;\
			float y = iResolution.y * fragTexcoord.y * 10.0;\
			vec2 k = vec2(1.0/iResolution.x, 1.0/iResolution.y);\
			vec4 data0 = texture(iTex0, fragTexcoord);\
			vec4 data1 = texture(iTex1, fragTexcoord);\
			vec3 _color = data0.rgb;\
			float _depth = data0.a;\
			\
			color = vec4(_color, 1.0);\
			\
			//color.rgb = mix(color.rgb, vec3(1.0), 1.0-_depth);\n\
		}\n\
	";
	render->shaderManager->fragmentShader = ERenderShader.create(fragment_src, sizeof(fragment_src), GL_FRAGMENT_SHADER);

	ERenderShaderManager.prepareShaders(render->shaderManager);

	glUniform1i(glGetUniformLocation(render->shaderManager->shader_id, "iTex0") , 0);
	glUniform1i(glGetUniformLocation(render->shaderManager->shader_id, "iTex1") , 1);
	glUniform1i(glGetUniformLocation(render->shaderManager->shader_id, "iTex2") , 2);
	glUniform1i(glGetUniformLocation(render->shaderManager->shader_id, "iTex3") , 3);

	glBindBuffer(GL_ARRAY_BUFFER, render->block_VBO);
	GLint positionLocation = glGetAttribLocation(render->shaderManager->shader_id, "iPosition");;
	glVertexAttribPointer(positionLocation, 2, GL_FLOAT, GL_FALSE, 4*sizeof(float), 0);
	glEnableVertexAttribArray(positionLocation);

	GLint texcoordLocation = glGetAttribLocation(render->shaderManager->shader_id, "iTexcoord");;
	glVertexAttribPointer(texcoordLocation, 2, GL_FLOAT, GL_FALSE, 4*sizeof(float), (const GLvoid*)(sizeof(float)*2) );
	glEnableVertexAttribArray(texcoordLocation);
}

void ERender_renderRect(ERenderInstance_p render)
{
	ERenderShaderManager.prepareShaders(render->shaderManager);

	glUniform2f(glGetUniformLocation(render->shaderManager->shader_id, "iResolution") , render->width, render->height);

	glBindVertexArray(render->block_VAO);

	glDrawArrays(GL_TRIANGLES, 0, 6);
}



void ERenderSetScene(const ERenderInstance_p render, const ERenderSceneInstance_p scene)
{
	render->scene = scene;
}


void ERenderRender(const ERenderInstance_p render)
{
	RenderEvent event_beforeRender = {type: beforeRender, render: render};
	RenderEvent event_afterRender = {type: afterRender, render: render};

	EEvents.addEvent(render->events, &event_beforeRender);

	ERenderCamera.renderScene(render->camera, render->scene);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, render->camera->color[0]);

	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, render->camera->color[1]);

	ERender_renderRect(render);

	EGui.render(render->gui);

	EEvents.addEvent(render->events, &event_afterRender);
}


_ERender ERender = {
	create: 		ERenderCreate,
	render: 		ERenderRender,
	setScene: 		ERenderSetScene,
};