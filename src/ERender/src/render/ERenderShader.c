#include <render/ERenderShader.h>
#include <render/ERenderOpenGL.h>

GLenum getShaderType(char* filename)
{
	return GL_FRAGMENT_SHADER;

	// GL_COMPUTE_SHADER, GL_VERTEX_SHADER, GL_TESS_CONTROL_SHADER, GL_TESS_EVALUATION_SHADER, GL_GEOMETRY_SHADER, or GL_FRAGMENT_SHADER
}

ERenderShaderInstance_p ERenderShaderCreate(char* src, int length, GLenum type)
{
	ERenderShaderInstance_p shader = EMem.alloc(sizeof(ERenderShaderInstance));

	shader->type = type;
	shader->_hash = ETools.hashString(src);
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

	if( !ETools.loadFile(filename, &buffer, &length) ){
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
	ERenderShaderManagerInstance_p shaderManager = EMem.alloc(sizeof(ERenderShaderManagerInstance));
	shaderManager->shader_id = glCreateProgram();
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
