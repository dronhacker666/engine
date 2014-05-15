#include "ERenderMaterial.h"

ERenderMaterialInstance_p ERenderMaterial_create(void)
{
	ERenderMaterialInstance_p mtl = EMem.alloc(sizeof(ERenderMaterialInstance));
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

	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glHint(GL_GENERATE_MIPMAP_HINT, GL_NICEST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_BASE_LEVEL, 0);
	glTexParameteri(GL_TEXTURE_2D, GL_GENERATE_MIPMAP, GL_TRUE); 

	// загрузим данные о цвете в текущую автивную текстуру
	glTexImage2D(
		GL_TEXTURE_2D,
		0,
		image.depth==24 ? GL_RGB8 : GL_RGBA8,
		image.width,
		image.height,
		0,
		image.depth==24 ? (image.colorSpace==RGB?GL_RGB:GL_BGR) : (image.colorSpace==RGB?GL_RGBA:GL_BGRA),
		GL_UNSIGNED_BYTE,
		image.data
	);
	EMem.free(image.data);

	glGenerateMipmap(GL_TEXTURE_2D);

	mtl->tex[index] = texture;

	return true;
}

_ERenderMaterial ERenderMaterial = {
	create: ERenderMaterial_create,
	loadTexture: ERenderMaterial_loadTexture,
};