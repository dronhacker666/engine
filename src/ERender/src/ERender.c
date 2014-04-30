#include "ERender.h"
#include "ERenderOpenGL.h"

ERenderInstance_p ERenderCreate(ERenderCreateOptions_p options){

	ERenderInstance_p render = malloc(sizeof(ERenderInstance));

	if( !ERenderOGLInit(options, &render->gAPI) ){
		return false;
	}

	render->viewport_x = 0;
	render->viewport_y = 0;
	render->viewport_width = options->width;
	render->viewport_height = options->height;

	render->shader = malloc(sizeof(ERenderShaderProgram));

	return render;
}

ESceneInstance_p ERenderCreateScene(void)
{
	return (ESceneInstance_p)eArray.create(sizeof(int));
}

void ERenderSetScene(ERenderInstance_p render, ESceneInstance_p scene)
{
	render->scene = scene;
}

/*void ERenderPrepareShaders(ERenderInstance_p render){
	if(render->shadersHasChanged){

		GLint status;
		char* buffer;

		GLuint shaderProgram = glCreateProgram();
		if(render->fragmentShader){
			glAttachShader(shaderProgram, render->fragmentShader->_gl_id);
		}
		if(render->vertexShader){
			glAttachShader(shaderProgram, render->vertexShader->_gl_id);
		}

		glLinkProgram(shaderProgram);
		glGetProgramiv(shaderProgram, GL_LINK_STATUS, &status);
		if (status != GL_TRUE){
			glGetProgramInfoLog(shaderProgram, 1024, 0, buffer);
			printf("Shader Program Link Error: %s\n", buffer);
			exit(1);
		}

		glValidateProgram(shaderProgram);
		glGetProgramiv(shaderProgram, GL_VALIDATE_STATUS, &status);
		if (status != GL_TRUE){
			glGetProgramInfoLog(shaderProgram, 1024, 0, buffer);
			printf("Shader Program Validate Error: %s\n", buffer);
			exit(1);
		}

		glUseProgram(shaderProgram);

		render->shadersHasChanged = true;
	}
}*/

void ERenderRender(ERenderInstance_p render)
{
	//ERenderPrepareShaders(render);

	glClearColor(0.8, 0.8, 0.8, 0.0);
	glShadeModel(GL_FLAT);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glColor3f(0.0, 0.0, 0.0);

	glBegin(GL_LINES);
	glVertex3f(100.0f, 100.0f, 0.0f);
	glVertex3f(200.0f, 140.0f, 5.0f);
	glEnd( );

	glBegin(GL_TRIANGLES);
	glVertex3f(10.0f, 10.0f, 0.0f);
	glVertex3f(15.0f, 10.0f, 0.0f);
	glVertex3f(12.0f, 5.0f, 0.0f);
	glEnd();

	SwapBuffers(render->gAPI.hdc);
}


_ERender ERender = {
	create: ERenderCreate,
	render: ERenderRender,
	setScene: ERenderSetScene,
	createScene: ERenderCreateScene,
};