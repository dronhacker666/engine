#include <render/ERenderOpenGL.h>
#include <render/ERenderEvents.h>
#include <input/EInput.h>

PFNWGLCREATECONTEXTATTRIBSARBPROC wglCreateContextAttribsARB = NULL;

PFNGLACTIVETEXTUREPROC glActiveTexture = NULL;
PFNGLGENERATEMIPMAPPROC glGenerateMipmap = NULL;

//FBO
PFNGLGENFRAMEBUFFERSPROC 		glGenFramebuffers 	 = NULL;
PFNGLBINDFRAMEBUFFERPROC 		glBindFramebuffer 	 = NULL;
PFNGLFRAMEBUFFERTEXTUREPROC 	glFramebufferTexture = NULL;
PFNGLDRAWBUFFERSPROC 			glDrawBuffers = NULL;
PFNGLBINDFRAGDATALOCATIONPROC 	glBindFragDataLocation = NULL;
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
PFNGLUNIFORM2FPROC   		glUniform2f		     = NULL;
PFNGLUNIFORM4FPROC   		glUniform4f		     = NULL;
PFNGLUNIFORM1IPROC   		glUniform1i		     = NULL;
PFNGLUNIFORM2IPROC   		glUniform2i		     = NULL;
PFNGLUNIFORM2FVPROC			glUniform2fv		 = NULL;
PFNGLUNIFORM3FVPROC			glUniform3fv		 = NULL;
PFNGLUNIFORM2IVPROC			glUniform2iv		 = NULL;

BOOL _initOpenGLProc(void)
{
	glActiveTexture = (PFNGLACTIVETEXTUREPROC)wglGetProcAddress("glActiveTexture");
	glGenerateMipmap = (PFNGLGENERATEMIPMAPPROC)wglGetProcAddress("glGenerateMipmap");
	
	//FBO
	glGenFramebuffers = (PFNGLGENFRAMEBUFFERSPROC)wglGetProcAddress("glGenFramebuffers");
	glBindFramebuffer = (PFNGLBINDFRAMEBUFFERPROC)wglGetProcAddress("glBindFramebuffer");
	glFramebufferTexture = (PFNGLFRAMEBUFFERTEXTUREPROC)wglGetProcAddress("glFramebufferTexture");
	glDrawBuffers = (PFNGLDRAWBUFFERSPROC)wglGetProcAddress("glDrawBuffers");
	glBindFragDataLocation = (PFNGLBINDFRAGDATALOCATIONPROC)wglGetProcAddress("glBindFragDataLocation");
	//VAO
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
	glUniform2f = (PFNGLUNIFORM2FPROC)wglGetProcAddress("glUniform2f");
	glUniform4f = (PFNGLUNIFORM4FPROC)wglGetProcAddress("glUniform4f");
	glUniform1i = (PFNGLUNIFORM1IPROC)wglGetProcAddress("glUniform1i");
	glUniform2i = (PFNGLUNIFORM2IPROC)wglGetProcAddress("glUniform2i");
	glUniform2fv = (PFNGLUNIFORM2FVPROC)wglGetProcAddress("glUniform2fv");
	glUniform3fv = (PFNGLUNIFORM2FVPROC)wglGetProcAddress("glUniform3fv");
	glUniform2iv = (PFNGLUNIFORM2IVPROC)wglGetProcAddress("glUniform2iv");

	return TRUE;
}

ERenderInstance_p render;


void changeWindowSize(ERenderInstance_p render, int width, int height)
{
	render->width = width;
	render->height = height;
	glViewport(0, 0, width, height);
}


LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	KeyboardEvent event;
	switch (uMsg)
	{
		case WM_KEYDOWN:
			event.type = keyDown;
			event.keyCode = wParam;
			EEvents.addEvent(render->events, &event);
		break;
		case WM_KEYUP:
			event.type = keyUp;
			event.keyCode = wParam;
			EEvents.addEvent(render->events, &event);
		break;
		case WM_SIZE:
			//changeWindowSize(render, LOWORD(lParam), HIWORD(lParam));
		break;
		case WM_DESTROY:
			PostQuitMessage(0);
			return 0;
	}
	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}


void ERenderOpenGL_onBeforeRender(RenderEvent_p event)
{
	MSG msg;
	while (PeekMessage(&msg, event->render->gAPI.hWnd, 0, 0, PM_NOREMOVE))
	{
		GetMessage(&msg, event->render->gAPI.hWnd, 0, 0);
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void ERenderOpenGL_onAfterRender(RenderEvent_p event)
{
	//glFlush();
	SwapBuffers(event->render->gAPI.hdc);
}

BOOL ERenderOGLInit(ERenderInstance_p render)
{
	printf(
		"Init gApi(%ix%i)\n",
		render->width,
		render->height
	);

	EEvents.addListener(render->events, beforeRender, (void*)ERenderOpenGL_onBeforeRender);
	EEvents.addListener(render->events, afterRender, (void*)ERenderOpenGL_onAfterRender);

	GAPI* gApi = &render->gAPI;

	WNDCLASSEX wc = {
		cbSize: sizeof(WNDCLASSEX),
		style: CS_VREDRAW | CS_HREDRAW,
		lpfnWndProc: &WindowProc,
		cbClsExtra: 0,
		cbWndExtra: 0,
		hInstance: GetModuleHandle(NULL),
		hIcon: NULL,
		hCursor: NULL,
		hbrBackground: NULL,
		lpszMenuName: NULL,
		lpszClassName: "myclass",
		hIconSm: NULL,
	};
	RegisterClassEx(&wc);

	int x = 0;// (GetSystemMetrics(SM_CXSCREEN) - render->width)  / 2;
	int y = 0;// (GetSystemMetrics(SM_CYSCREEN) - render->height) / 2;

	gApi->hWnd = CreateWindowEx(WS_EX_TOPMOST, "myclass", "Game", WS_VISIBLE|WS_POPUP, x, y, render->width, render->height, 0, 0, 0, 0);
	gApi->hdc = GetDC(gApi->hWnd);

	PIXELFORMATDESCRIPTOR ppfd;
	ppfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
	ppfd.iPixelType = PFD_TYPE_RGBA;
	ppfd.cColorBits = 32;
	ppfd.dwLayerMask = PFD_MAIN_PLANE;
	int iPixelFormat = ChoosePixelFormat(gApi->hdc, &ppfd);
	SetPixelFormat(gApi->hdc, iPixelFormat, &ppfd);

	HGLRC hGLRC = wglCreateContext(gApi->hdc);
	wglMakeCurrent(gApi->hdc, hGLRC);

	wglCreateContextAttribsARB = (PFNWGLCREATECONTEXTATTRIBSARBPROC)wglGetProcAddress("wglCreateContextAttribsARB");

	if(!wglCreateContextAttribsARB){
		printf("wglCreateContextAttribsARB fail (%ld)\n", GetLastError());
		return FALSE;
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
		printf("Creating gApi context fail (%ld)\n", GetLastError());
		return FALSE;
	}

	if(! _initOpenGLProc() ){
		return FALSE;
	}

	printf("OpenGL gApi context information:\n");

	printf("Renderer     : %s\n", (const char*)glGetString(GL_RENDERER));
	printf("Version      : %s\n", (const char*)glGetString(GL_VERSION));
	printf("GLSL version : %s\n", (const char*)glGetString(GL_SHADING_LANGUAGE_VERSION));

	glClearDepth(1.0f);
	glClearColor(0.6, 0.6, 0.6, 0.0);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	glViewport(0, 0, render->width, render->height);

	return TRUE;
}



GLuint TextureCreate(GLint internalFormat, GLenum format, GLsizei width, GLsizei height, const GLvoid * data, bool genMipmap)
{
	GLuint texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	if(genMipmap){
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glHint(GL_GENERATE_MIPMAP_HINT, GL_NICEST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_BASE_LEVEL, 0);
		glTexParameteri(GL_TEXTURE_2D, GL_GENERATE_MIPMAP, GL_TRUE); 
	}else{
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	}

	glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, width, height, 0, format, GL_UNSIGNED_BYTE, data);

	if(genMipmap){
		glGenerateMipmap(GL_TEXTURE_2D);
	}

	return texture;
}