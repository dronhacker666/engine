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

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	// установим параметры "оборачивания" текстуры - отсутствие оборачивания
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

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

	free(image.data);

	return texture;
}


_ERenderTexture ERenderTexture = {
	load: ERenderTextureLoad,
};