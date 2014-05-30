#include <stdio.h>
#include <ft2build.h>
#include <freetype/freetype.h>
#include <freetype/ftglyph.h>
#include <freetype/ftoutln.h>
#include <freetype/fttrigon.h>

#include "headers.h"

int main(void)
{
	FILE* fp = fopen("../data/arial.my", "wb");

	FT_Face face;
	FT_Library ft;

	FT_Init_FreeType(&ft);
	FT_New_Face(ft, "../data/arial.ttf", 0, &face);

	FT_GlyphSlot g = face->glyph;

	unsigned char size;
	int code;
	FChar ch;
	FCharset chset;
	long int pos1, pos2;
	unsigned int dataSize;

	for(size=10; size<=14; size++)
	{
		FT_Set_Pixel_Sizes(face, 0, size);
		pos1 = ftell(fp);
		fseek(fp, sizeof(FCharset), SEEK_CUR);
		dataSize=0;
		for(code=0; code<2000; code++)
		{
			FT_Load_Char(face, code, FT_LOAD_RENDER);

			ch.code = code;
			ch.width = g->bitmap.width;
			ch.height = g->bitmap.rows;
			ch.top = g->bitmap_top;
			ch.left = g->bitmap_left;
			ch._dataSize = sizeof(char) * ch.width * ch.height;

			fwrite(&ch, sizeof(FChar), 1, fp);
			fwrite(g->bitmap.buffer, ch._dataSize, 1, fp);
			dataSize += ch._dataSize + sizeof(FChar);
		}
		pos2 = ftell(fp);
		chset.fontSize = size;
		chset._dataSize = dataSize;
		fseek(fp, pos1, SEEK_SET);
		fwrite(&chset, sizeof(FCharset), 1, fp);
		fseek(fp, pos2, SEEK_SET);
	}

	fclose(fp);

	FT_Done_Face(face);
	FT_Done_FreeType(ft);

	return 0;
}