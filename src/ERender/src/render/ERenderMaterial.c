#include "ERenderMaterial.h"

unsigned int id=0;

ERenderMaterialInstance_p ERenderMaterial_create(void)
{
	ERenderMaterialInstance_p mtl = EMem.alloc(sizeof(ERenderMaterialInstance));
	mtl->id = id++;
	return mtl;
}

bool ERenderMaterial_loadTexture(ERenderMaterialInstance_p mtl, const char* filename, GLuint index)
{
	Image image;
	GLuint texture;

	bool ok;
	int length = strlen(filename);

	if( memcmp(filename+length-4, ".tga", 4)==0 ){
		ok = loadTGA(filename, &image);
	}
	else if( memcmp(filename+length-4, ".jpg", 4)==0 || memcmp(filename+length-5, ".jpeg", 5)==0 ){
		ok = loadJPEG(filename, &image);
	}
	else{
		printf("ERenderTexture error: unknown format \"%s\"\n", filename);
		exit(0);
	}

	if( !ok ){
		return 0;
	}

	mtl->tex[index] = TextureCreate(
		image.depth==24 ? GL_RGB8 : GL_RGBA8,
		image.depth==24 ? (image.colorSpace==RGB?GL_RGB:GL_BGR) : (image.colorSpace==RGB?GL_RGBA:GL_BGRA),
		image.width,
		image.height,
		image.data,
		true
	);
	EMem.free(image.data);

	glActiveTexture(GL_TEXTURE0 + mtl->id+1);
	glBindTexture(GL_TEXTURE_2D, mtl->tex[index]);

	return true;
}

_ERenderMaterial ERenderMaterial = {
	create: ERenderMaterial_create,
	loadTexture: ERenderMaterial_loadTexture,
};