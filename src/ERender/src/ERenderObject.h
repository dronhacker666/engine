#ifndef erender_object_h
#define erender_object_h

#include <GL/GL.h>

typedef struct {
	GLuint fragmentShader;
	GLuint vertexShader;

	GLuint vbo;

} ERenderObject, *ERenderObject_p;

#endif