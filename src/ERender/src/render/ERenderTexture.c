#include "ERenderTexture.h"
#include "ERenderOpenGL.h"

GLuint ERenderTextureLoad(char* filename)
{
	Image image;
	GLuint texture;
	if( !loadTGA(filename, &image) ){
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
		image.depth==24 ? GL_BGR : GL_BGRA,
		GL_UNSIGNED_BYTE,
		image.data
	);
	EMem.free(image.data);

	glGenerateMipmap(GL_TEXTURE_2D);

	return texture;
}


_ERenderTexture ERenderTexture = {
	load: ERenderTextureLoad,
};