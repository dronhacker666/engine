#include <imageDecoder/TGA.h>
#include <assert.h>

bool loadTGA(const char* filename, Image_p out)
{
	assert(filename);

	TGAHeader *header;
	char *buffer;
	int size;

	if(!ETools.loadFile(filename, &buffer, &size))
	{
		return 0;
	}

	// если размер файла заведомо меньше заголовка TGA
	if (size <= sizeof(TGAHeader))
	{
		printf("Too small file '%s'\n", filename);
		EMem.free(buffer);
		return 0;
	}

	header = (TGAHeader*)buffer;

	// проверим формат TGA-файла - несжатое RGB или RGBA изображение
	if (header->datatype != 2 || (header->bitperpel != 24 && header->bitperpel != 32))
	{
		printf("Wrong TGA format '%s'\n", filename);
		EMem.free(buffer);
		return 0;
	}

	out->width = header->width;
	out->height = header->height;
	out->depth = header->bitperpel;
	out->colorSpace = BGR;
	out->data = (void*)(buffer + sizeof(TGAHeader) + header->idlength);

	return 1;
}