#include "ERenderShader.h"
#include "ERenderOpenGL.h"

GLenum getShaderType(char* filename)
{
	return GL_FRAGMENT_SHADER;

	// GL_COMPUTE_SHADER, GL_VERTEX_SHADER, GL_TESS_CONTROL_SHADER, GL_TESS_EVALUATION_SHADER, GL_GEOMETRY_SHADER, or GL_FRAGMENT_SHADER
}

ERenderShaderInstance_p ERenderShaderCreate(char* src, int length, GLenum type)
{
	new(shader, ERenderShaderInstance);

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
	char* buffer;
	int length;

	if( !eTools.loadFile(filename, &buffer, &length) ){
		return NULL;
	}

	return ERenderShaderCreate(buffer, length, getShaderType(filename));
}

_ERenderShader ERenderShader = {
	create: ERenderShaderCreate,
	load: ERenderShaderLoad,
};



/**
*	Shader Manager
*/

ERenderShaderManagerInstance_p ERenderShaderManagerCreate(void)
{
	new(shaderManager, ERenderShaderManagerInstance);

	shaderManager->shader_id = glCreateProgram();

	char vertex_src[] = "\
		#version 140\n\
		uniform mat4 viewMatrix;\n\
		uniform mat4 modelMatrix;\n\
		in vec3 iPosition;\n\
		in vec2 iTexcoord;\n\
		out vec2 fragTexcoord;\n\
		void main(void)\n\
		{\n\
			gl_Position   =  viewMatrix * (modelMatrix * vec4(iPosition, 1.0));\n\
			fragTexcoord  = iTexcoord;\n\
		}\n\
	";
	shaderManager->vertexShader = ERenderShaderCreate(vertex_src, sizeof(vertex_src), GL_VERTEX_SHADER);

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
	shaderManager->fragmentShader = ERenderShaderCreate(fragment_src, sizeof(fragment_src), GL_FRAGMENT_SHADER);

	shaderManager->needRelink = TRUE;

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

		shaderManager->needRelink = FALSE;
	}
	glUseProgram(shaderManager->shader_id);
}

_ERenderShaderManager ERenderShaderManager = {
	create: 			ERenderShaderManagerCreate,
	prepareShaders: 	ERenderShaderManagerPrepareShaders,
};
