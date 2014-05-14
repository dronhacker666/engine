#ifndef ERENDERSHADER_H
#define ERENDERSHADER_H


#include <windows.h>
#include <GL/GL.h>
#include <GL/wglext.h>
#include <GL/glext.h>
#include "ELib.h"

/**
*	Shader Instance
*/

typedef struct {
	GLuint _gl_id;
	unsigned int _hash;

	GLenum type; // GL_COMPUTE_SHADER, GL_VERTEX_SHADER, GL_TESS_CONTROL_SHADER, GL_TESS_EVALUATION_SHADER, GL_GEOMETRY_SHADER, or GL_FRAGMENT_SHADER
} ERenderShaderInstance, *ERenderShaderInstance_p;

typedef struct {
	ERenderShaderInstance_p (*create)	(char* src, int length, GLenum type);
	ERenderShaderInstance_p (*load) 	(char*);
} _ERenderShader;
extern _ERenderShader ERenderShader;



/**
*	Shader Manager
*/

typedef struct {
	GLuint shader_id;
	ERenderShaderInstance_p fragmentShader;
	ERenderShaderInstance_p vertexShader;

	BOOL needRelink;

} ERenderShaderManagerInstance, *ERenderShaderManagerInstance_p;

typedef struct {
	ERenderShaderManagerInstance_p 	(*create) 			(void);
	void							(*prepareShaders) 	(ERenderShaderManagerInstance_p);
} _ERenderShaderManager;
extern _ERenderShaderManager ERenderShaderManager;

#endif