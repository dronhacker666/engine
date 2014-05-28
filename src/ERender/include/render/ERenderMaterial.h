#ifndef ERENDERMATERIAL_H
#define ERENDERMATERIAL_H

#include <ELib.h>
#include <imageDecoder/Image.h>
#include "ERenderOpenGL.h"

typedef struct {
	unsigned int id;
	GLuint tex[10];

} ERenderMaterialInstance, *ERenderMaterialInstance_p;

typedef struct {
	ERenderMaterialInstance_p 	(*create) 		(void);
	bool 						(*loadTexture) 	(ERenderMaterialInstance_p, const char*, GLuint);
} _ERenderMaterial;
extern _ERenderMaterial ERenderMaterial;

#endif