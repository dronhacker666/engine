#include "JPEG.h"

bool loadJPEG(char* filename, Image_p out)
{
	FILE *fd;
	struct jpeg_decompress_struct cinfo;
	struct jpeg_error_mgr jerr;
	void* line;

	cinfo.err = jpeg_std_error(&jerr);
	jpeg_create_decompress(&cinfo);

	if (NULL == (fd = fopen(filename, "rb"))){
		return false;
	}

	jpeg_stdio_src(&cinfo, fd);
	jpeg_read_header(&cinfo, TRUE);

	jpeg_start_decompress (&cinfo);

	out->data = EMem.alloc( cinfo.output_width * cinfo.output_height * cinfo.num_components );
	out->width = cinfo.output_width;
	out->height = cinfo.output_height;
	out->depth = cinfo.num_components * 8;
	out->colorSpace = cinfo.jpeg_color_space == JCS_RGB ? RGB : BGR;

	int line_size = cinfo.output_width * cinfo.num_components;
	while (cinfo.output_scanline < cinfo.output_height)
	{
		line = out->data+(line_size * (cinfo.output_height - cinfo.output_scanline - 1) );
		jpeg_read_scanlines (&cinfo, (JSAMPARRAY)&line, 1);
	}

	jpeg_finish_decompress (&cinfo);
	jpeg_destroy_decompress (&cinfo);

	return true;
}