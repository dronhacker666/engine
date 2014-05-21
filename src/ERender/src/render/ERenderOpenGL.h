#ifndef OPENGL_H
#define OPENGL_H

#include <windows.h>
#include <GL/gl.h>
#include <GL/glext.h>
#include <GL/wglext.h>
#include "ERender.h"

BOOL ERenderOGLInit(ERenderInstance_p);

GLuint TextureCreate(GLint, GLenum, GLsizei, GLsizei, const GLvoid*, bool);

/* OPENGL EXTENSIONS */
extern PFNWGLCREATECONTEXTATTRIBSARBPROC wglCreateContextAttribsARB;

extern PFNGLACTIVETEXTUREPROC glActiveTexture;
extern PFNGLGENERATEMIPMAPPROC glGenerateMipmap;

//FBO
extern PFNGLGENFRAMEBUFFERSPROC 		glGenFramebuffers;
extern PFNGLBINDFRAMEBUFFERPROC 		glBindFramebuffer;
extern PFNGLFRAMEBUFFERTEXTUREPROC 		glFramebufferTexture;
extern PFNGLDRAWBUFFERSPROC 			glDrawBuffers;
extern PFNGLBINDFRAGDATALOCATIONPROC 	glBindFragDataLocation;

// VAO
extern PFNGLGENVERTEXARRAYSPROC    glGenVertexArrays;
extern PFNGLDELETEVERTEXARRAYSPROC glDeleteVertexArrays;
extern PFNGLBINDVERTEXARRAYPROC    glBindVertexArray;
// VBO
extern PFNGLGENBUFFERSPROC    glGenBuffers;
extern PFNGLDELETEBUFFERSPROC glDeleteBuffers;
extern PFNGLBINDBUFFERPROC    glBindBuffer;
extern PFNGLBUFFERDATAPROC    glBufferData;
extern PFNGLBUFFERSUBDATAPROC glBufferSubData;
// Shaders
extern PFNGLCREATEPROGRAMPROC     glCreateProgram;
extern PFNGLDELETEPROGRAMPROC     glDeleteProgram;
extern PFNGLLINKPROGRAMPROC       glLinkProgram;
extern PFNGLVALIDATEPROGRAMPROC   glValidateProgram;
extern PFNGLUSEPROGRAMPROC        glUseProgram;
extern PFNGLGETPROGRAMIVPROC      glGetProgramiv;
extern PFNGLGETPROGRAMINFOLOGPROC glGetProgramInfoLog;
extern PFNGLCREATESHADERPROC      glCreateShader;
extern PFNGLDELETESHADERPROC      glDeleteShader;
extern PFNGLSHADERSOURCEPROC      glShaderSource;
extern PFNGLCOMPILESHADERPROC     glCompileShader;
extern PFNGLATTACHSHADERPROC      glAttachShader;
extern PFNGLDETACHSHADERPROC      glDetachShader;
extern PFNGLGETSHADERIVPROC       glGetShaderiv;
extern PFNGLGETSHADERINFOLOGPROC  glGetShaderInfoLog;
// Shaders attributes
extern PFNGLGETATTRIBLOCATIONPROC        glGetAttribLocation;
extern PFNGLVERTEXATTRIBPOINTERPROC      glVertexAttribPointer;
extern PFNGLENABLEVERTEXATTRIBARRAYPROC  glEnableVertexAttribArray;
extern PFNGLDISABLEVERTEXATTRIBARRAYPROC glDisableVertexAttribArray;
// Shaders uniforms
extern PFNGLGETUNIFORMLOCATIONPROC glGetUniformLocation;
extern PFNGLUNIFORMMATRIX4FVPROC   glUniformMatrix4fv;
extern PFNGLUNIFORM1FPROC   	   glUniform1f;
extern PFNGLUNIFORM2FPROC   	   glUniform2f;
extern PFNGLUNIFORM4FPROC   	   glUniform4f;
extern PFNGLUNIFORM1IPROC   	   glUniform1i;
extern PFNGLUNIFORM2IPROC   	   glUniform2i;
extern PFNGLUNIFORM2FVPROC		   glUniform2fv;
extern PFNGLUNIFORM2IVPROC		   glUniform2iv;

#endif