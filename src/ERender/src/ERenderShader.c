#include "ERenderShader.h"
#include "ERenderOpenGL.h"

GLenum getShaderType(char* filename)
{
	return GL_FRAGMENT_SHADER;

	// GL_COMPUTE_SHADER, GL_VERTEX_SHADER, GL_TESS_CONTROL_SHADER, GL_TESS_EVALUATION_SHADER, GL_GEOMETRY_SHADER, or GL_FRAGMENT_SHADER
}

ERenderShaderInstance_p ERenderShaderCreate(char* src, int length, GLenum type)
{
	ERenderShaderInstance_p shader = malloc(sizeof(ERenderShaderInstance));

	shader->type = type;
	shader->_hash = eTools.hashString(src);
	shader->_gl_id = glCreateShader(shader->type);

	glShaderSource(shader->_gl_id, 1, (const GLchar**)&src, (const GLint*)&length);
	glCompileShader(shader->_gl_id);

	GLint status;
	char buffer[1024];
	glGetShaderiv(shader->_gl_id, GL_COMPILE_STATUS, &status);

	if (status != GL_TRUE){
		glGetShaderInfoLog(shader->_gl_id, 1024, 0, buffer);
		printf("Shader Error: %s\n", buffer);
		exit(1);
	}

	return shader;
}

ERenderShaderInstance_p ERenderShaderLoad(char* filename)
{
	FileResult shader_src = eTools.loadFile(filename);
	if(shader_src.success)
	{
		return ERenderShaderCreate(shader_src.content, shader_src.length, getShaderType(filename));
	}else{
		return NULL;
	}
}

_ERenderShader ERenderShader = {
	load: ERenderShaderLoad,
};



/**
*	Shader Manager
*/

ERenderShaderManagerInstance_p ERenderShaderManagerCreate(void)
{
	ERenderShaderManagerInstance_p shaderManager = malloc(sizeof(ERenderShaderManagerInstance));

	shaderManager->shader_id = glCreateProgram();

	char vertex_src[] = "\
		#version 140\n\
		uniform mat4 viewMatrix;\n\
		uniform mat4 modelMatrix;\n\
		in vec3 position;\n\
		void main(void)\n\
		{\n\
			vec4 vertex   = modelMatrix * vec4(position, 1.0);\n\
			gl_Position   = viewMatrix * vertex;\n\
		}\n\
	";
	shaderManager->vertexShader = ERenderShaderCreate(vertex_src, sizeof(vertex_src), GL_VERTEX_SHADER);

	char fragment_src[] = "\
		#version 140\n\
		out vec4 gl_FragColor;\n\
		void main(void)\n\
		{\n\
			gl_FragColor = vec4(1.0, 1.0, 1.0, 1.0);\n\
		}\n\
	";
	shaderManager->fragmentShader = ERenderShaderCreate(fragment_src, sizeof(fragment_src), GL_FRAGMENT_SHADER);

	shaderManager->needRelink = true;

	return shaderManager;
}

void ERenderShaderManagerPrepareShaders(ERenderShaderManagerInstance_p shaderManager)
{
	if(shaderManager->needRelink){

		GLint status;
		char buffer[1024];

		if(shaderManager->fragmentShader){
			glAttachShader(shaderManager->shader_id, shaderManager->fragmentShader->_gl_id);
		}
		if(shaderManager->vertexShader){
			glAttachShader(shaderManager->shader_id, shaderManager->vertexShader->_gl_id);
		}

		glLinkProgram(shaderManager->shader_id);
		glGetProgramiv(shaderManager->shader_id, GL_LINK_STATUS, &status);
		if (status != GL_TRUE){
			glGetProgramInfoLog(shaderManager->shader_id, 1024, 0, buffer);
			printf("Shader Program Link Error: %s\n", buffer);
			exit(1);
		}

		glValidateProgram(shaderManager->shader_id);
		glGetProgramiv(shaderManager->shader_id, GL_VALIDATE_STATUS, &status);
		if (status != GL_TRUE){
			glGetProgramInfoLog(shaderManager->shader_id, 1024, 0, buffer);
			printf("Shader Program Validate Error: %s\n", buffer);
			exit(1);
		}

		glUseProgram(shaderManager->shader_id);

		shaderManager->needRelink = false;
	}
}

_ERenderShaderManager ERenderShaderManager = {
	create: 			ERenderShaderManagerCreate,
	prepareShaders: 	ERenderShaderManagerPrepareShaders,
};
