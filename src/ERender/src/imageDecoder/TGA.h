#ifndef IMAGEDECODER_TGA_H
#define IMAGEDECODER_TGA_H

#include <stdint.h>
#include "Image.h"
#include "../../../ELib/include/ELib.h"

typedef struct
{
	uint8_t  idlength;
	uint8_t  colormap;
	uint8_t  datatype;
	uint8_t  colormapinfo[5];
	uint16_t xorigin;
	uint16_t yorigin;
	uint16_t width;
	uint16_t height;
	uint8_t  bitperpel;
	uint8_t  description;
} TGAHeader;

bool loadTGA(char*, Image_p);

#endif