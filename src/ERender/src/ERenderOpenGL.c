#include "ERenderOpenGL.h"

PFNWGLCREATECONTEXTATTRIBSARBPROC wglCreateContextAttribsARB = NULL;

// VAO
PFNGLGENVERTEXARRAYSPROC    glGenVertexArrays    = NULL;
PFNGLDELETEVERTEXARRAYSPROC glDeleteVertexArrays = NULL;
PFNGLBINDVERTEXARRAYPROC    glBindVertexArray    = NULL;
// VBO
PFNGLGENBUFFERSPROC    glGenBuffers    = NULL;
PFNGLDELETEBUFFERSPROC glDeleteBuffers = NULL;
PFNGLBINDBUFFERPROC    glBindBuffer    = NULL;
PFNGLBUFFERDATAPROC    glBufferData    = NULL;
PFNGLBUFFERSUBDATAPROC glBufferSubData = NULL;
// Shaders
PFNGLCREATEPROGRAMPROC     glCreateProgram     = NULL;
PFNGLDELETEPROGRAMPROC     glDeleteProgram     = NULL;
PFNGLLINKPROGRAMPROC       glLinkProgram       = NULL;
PFNGLVALIDATEPROGRAMPROC   glValidateProgram   = NULL;
PFNGLUSEPROGRAMPROC        glUseProgram        = NULL;
PFNGLGETPROGRAMIVPROC      glGetProgramiv      = NULL;
PFNGLGETPROGRAMINFOLOGPROC glGetProgramInfoLog = NULL;
PFNGLCREATESHADERPROC      glCreateShader      = NULL;
PFNGLDELETESHADERPROC      glDeleteShader      = NULL;
PFNGLSHADERSOURCEPROC      glShaderSource      = NULL;
PFNGLCOMPILESHADERPROC     glCompileShader     = NULL;
PFNGLATTACHSHADERPROC      glAttachShader      = NULL;
PFNGLDETACHSHADERPROC      glDetachShader      = NULL;
PFNGLGETSHADERIVPROC       glGetShaderiv       = NULL;
PFNGLGETSHADERINFOLOGPROC  glGetShaderInfoLog  = NULL;
// Shaders attributes
PFNGLGETATTRIBLOCATIONPROC        glGetAttribLocation        = NULL;
PFNGLVERTEXATTRIBPOINTERPROC      glVertexAttribPointer      = NULL;
PFNGLENABLEVERTEXATTRIBARRAYPROC  glEnableVertexAttribArray  = NULL;
PFNGLDISABLEVERTEXATTRIBARRAYPROC glDisableVertexAttribArray = NULL;
// Shaders uniforms
PFNGLGETUNIFORMLOCATIONPROC glGetUniformLocation = NULL;
PFNGLUNIFORMMATRIX4FVPROC   glUniformMatrix4fv   = NULL;
PFNGLUNIFORM1FPROC   		glUniform1f		     = NULL;
PFNGLUNIFORM2FVPROC			glUniform2fv		 = NULL;

bool _initOpenGLProc(void)
{
	glGenVertexArrays = (PFNGLGENVERTEXARRAYSPROC)wglGetProcAddress("glGenVertexArrays");
	glDeleteVertexArrays = (PFNGLDELETEVERTEXARRAYSPROC)wglGetProcAddress("glDeleteVertexArrays");
	glBindVertexArray = (PFNGLBINDVERTEXARRAYPROC)wglGetProcAddress("glBindVertexArray");
	// VBO
	glGenBuffers = (PFNGLGENBUFFERSPROC)wglGetProcAddress("glGenBuffers");
	glDeleteBuffers = (PFNGLDELETEBUFFERSPROC)wglGetProcAddress("glDeleteBuffers");
	glBindBuffer = (PFNGLBINDBUFFERPROC)wglGetProcAddress("glBindBuffer");
	glBufferData = (PFNGLBUFFERDATAPROC)wglGetProcAddress("glBufferData");
	glBufferSubData = (PFNGLBUFFERSUBDATAPROC)wglGetProcAddress("glBufferSubData");
	// Shaders
	glCreateProgram = (PFNGLCREATEPROGRAMPROC)wglGetProcAddress("glCreateProgram");
	glDeleteProgram = (PFNGLDELETEPROGRAMPROC)wglGetProcAddress("glDeleteProgram");
	glLinkProgram = (PFNGLLINKPROGRAMPROC)wglGetProcAddress("glLinkProgram");
	glValidateProgram = (PFNGLVALIDATEPROGRAMPROC)wglGetProcAddress("glValidateProgram");
	glUseProgram = (PFNGLUSEPROGRAMPROC)wglGetProcAddress("glUseProgram");
	glGetProgramiv = (PFNGLGETPROGRAMIVPROC)wglGetProcAddress("glGetProgramiv");
	glGetProgramInfoLog = (PFNGLGETPROGRAMINFOLOGPROC)wglGetProcAddress("glGetProgramInfoLog");
	glCreateShader = (PFNGLCREATESHADERPROC)wglGetProcAddress("glCreateShader");
	glDeleteShader = (PFNGLDELETESHADERPROC)wglGetProcAddress("glDeleteShader");
	glShaderSource = (PFNGLSHADERSOURCEPROC)wglGetProcAddress("glShaderSource");
	glCompileShader = (PFNGLCOMPILESHADERPROC)wglGetProcAddress("glCompileShader");
	glAttachShader = (PFNGLATTACHSHADERPROC)wglGetProcAddress("glAttachShader");
	glDetachShader = (PFNGLDETACHSHADERPROC)wglGetProcAddress("glDetachShader");
	glGetShaderiv = (PFNGLGETSHADERIVPROC)wglGetProcAddress("glGetShaderiv");
	glGetShaderInfoLog = (PFNGLGETSHADERINFOLOGPROC)wglGetProcAddress("glGetShaderInfoLog");
	// Shaders attributes
	glGetAttribLocation = (PFNGLGETATTRIBLOCATIONPROC)wglGetProcAddress("glGetAttribLocation");
	glVertexAttribPointer = (PFNGLVERTEXATTRIBPOINTERPROC)wglGetProcAddress("glVertexAttribPointer");
	glEnableVertexAttribArray = (PFNGLENABLEVERTEXATTRIBARRAYPROC)wglGetProcAddress("glEnableVertexAttribArray");
	glDisableVertexAttribArray = (PFNGLDISABLEVERTEXATTRIBARRAYPROC)wglGetProcAddress("glDisableVertexAttribArray");
	// Shaders uniforms
	glGetUniformLocation = (PFNGLGETUNIFORMLOCATIONPROC)wglGetProcAddress("glGetUniformLocation");
	glUniformMatrix4fv = (PFNGLUNIFORMMATRIX4FVPROC)wglGetProcAddress("glUniformMatrix4fv");
	glUniform1f = (PFNGLUNIFORM1FPROC)wglGetProcAddress("glUniform1f");
	glUniform2fv = (PFNGLUNIFORM2FVPROC)wglGetProcAddress("glUniform2fv");

	return true;
}

bool ERenderOGLInit(ERenderCreateOptions* options, GAPI* gApi)
{
	printf(
		"Init gApi(%ix%i)\n",
		options->width,
		options->height
	);

	gApi->hWnd = CreateWindowEx(WS_EX_TOPMOST, "edit", options->title, WS_VISIBLE|WS_POPUP, 0, 0, options->width, options->height, 0, 0, 0, 0);
	gApi->hdc = GetDC(gApi->hWnd);

	PIXELFORMATDESCRIPTOR ppfd;
	ppfd.dwFlags = PFD_DRAW_TO_WINDOW+PFD_SUPPORT_OPENGL+PFD_DOUBLEBUFFER;
	ppfd.iPixelType = PFD_TYPE_RGBA;
	ppfd.cColorBits = 32;
	ppfd.dwLayerMask = PFD_MAIN_PLANE;
	int iPixelFormat = ChoosePixelFormat(gApi->hdc, &ppfd);
	SetPixelFormat(gApi->hdc, iPixelFormat, &ppfd);

	HGLRC hGLRC = wglCreateContext(gApi->hdc);
	wglMakeCurrent(gApi->hdc, hGLRC);

	wglCreateContextAttribsARB = (PFNWGLCREATECONTEXTATTRIBSARBPROC)wglGetProcAddress("wglCreateContextAttribsARB");

	if(!wglCreateContextAttribsARB){
		printf("wglCreateContextAttribsARB fail (%d)\n", GetLastError());
		return false;
	}

	int maj, min;
	glGetIntegerv(GL_MAJOR_VERSION, &maj);
	glGetIntegerv(GL_MINOR_VERSION, &min);
	printf("Avaible OpengGL      : %i.%i\n", maj, min);

	int attr[] = {
		WGL_CONTEXT_MAJOR_VERSION_ARB, 3,
		WGL_CONTEXT_MINOR_VERSION_ARB, 1,
		WGL_CONTEXT_FLAGS_ARB,         WGL_CONTEXT_FORWARD_COMPATIBLE_BIT_ARB,
		WGL_CONTEXT_PROFILE_MASK_ARB,  WGL_CONTEXT_CORE_PROFILE_BIT_ARB,
		0
	};

	wglDeleteContext(hGLRC);
	hGLRC = wglCreateContextAttribsARB(gApi->hdc, 0, attr);

	if(!hGLRC || !wglMakeCurrent(gApi->hdc, hGLRC)){
		printf("Creating gApi context fail (%d)\n", GetLastError());
		return false;
	}

	if(! _initOpenGLProc() ){
		return false;
	}

	printf("OpenGL gApi context information:\n");

	printf("Renderer     : %s\n", (const char*)glGetString(GL_RENDERER));
	printf("Version      : %s\n", (const char*)glGetString(GL_VERSION));
	printf("GLSL version : %s\n", (const char*)glGetString(GL_SHADING_LANGUAGE_VERSION));

	return true;
}
