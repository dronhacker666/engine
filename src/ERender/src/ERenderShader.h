#ifndef ERENDERSHADER_H
#define ERENDERSHADER_H

#include <windows.h>
#include <GL/GL.h>
#include <GL/wglext.h>
#include <GL/glext.h>
#include "../../ELib/include/ELib.h"

typedef struct {
	GLuint _gl_id;
	unsigned int _hash;

	GLenum type; // GL_COMPUTE_SHADER, GL_VERTEX_SHADER, GL_TESS_CONTROL_SHADER, GL_TESS_EVALUATION_SHADER, GL_GEOMETRY_SHADER, or GL_FRAGMENT_SHADER
} ERenderShaderInstance, *ERenderShaderInstance_p;

typedef struct {
	GLuint shader_id;
	ERenderShaderInstance_p fragmentShader;
	ERenderShaderInstance_p vertexShader;
} ERenderShaderProgram, *ERenderShaderProgram_p;

typedef struct {
	ERenderShaderInstance_p (*create) (char*);
} _ERenderShader;
extern _ERenderShader ERenderShader;

#endif