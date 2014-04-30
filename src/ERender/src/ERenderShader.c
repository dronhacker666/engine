#include "ERenderShader.h"
#include "ERenderOpenGL.h"

GLenum getShaderType(char* filename)
{
	return GL_FRAGMENT_SHADER;

	// GL_COMPUTE_SHADER, GL_VERTEX_SHADER, GL_TESS_CONTROL_SHADER, GL_TESS_EVALUATION_SHADER, GL_GEOMETRY_SHADER, or GL_FRAGMENT_SHADER
}

ERenderShaderInstance_p ERenderShaderCreate(char* filename)
{
	FileResult shader_src = eTools.loadFile(filename);
	if(shader_src.success)
	{
		ERenderShaderInstance_p shader = malloc(sizeof(ERenderShaderInstance));

		shader->type = getShaderType(filename);
		shader->_hash = eTools.hashString(filename);
		shader->_gl_id = glCreateShader(shader->type);

		glShaderSource(shader->_gl_id, 1, &shader_src.content, &shader_src.length );
		glCompileShader(shader->_gl_id);

		GLint status;
		char* buffer;
		glGetShaderiv(shader->_gl_id, GL_COMPILE_STATUS, &status);
		if (status != GL_TRUE){
			glGetShaderInfoLog(shader->_gl_id, 1024, 0, buffer);
			printf("Shader Error: %s\n", buffer);
			return NULL;
		}

		return shader;
	}else{
		return NULL;
	}
}

_ERenderShader ERenderShader = {
	create: ERenderShaderCreate,
};
