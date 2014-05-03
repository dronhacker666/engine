#ifndef ERENDERTEXTURE_H
#define ERENDERTEXTURE_H

#include "imageDecoder/Image.h"
#include "imageDecoder/TGA.h"
#include "ERenderOpenGL.h"

typedef struct {
	GLuint _gl_id;
} ERenderTextureInstance, *ERenderTextureInstance_p;

typedef struct {
	GLuint (*load) (char*);
} _ERenderTexture;
extern _ERenderTexture ERenderTexture;

#endif