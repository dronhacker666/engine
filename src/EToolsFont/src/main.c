#include <stdio.h>
#include <ft2build.h>
#include <freetype/freetype.h>
#include <freetype/ftglyph.h>
#include <freetype/ftoutln.h>
#include <freetype/fttrigon.h>

typedef struct
{
	char code;
	char size;
	unsigned int width;
	unsigned int height;
	unsigned int _dataSize;
} FChar;

int main(void)
{

	FILE* fp = fopen("../data/arial.my", "wb");

	FT_Face face;
	FT_Library ft;

	FT_Init_FreeType(&ft);
	FT_New_Face(ft, "../data/arial.ttf", 0, &face);

	FT_GlyphSlot g = face->glyph;

	FT_Set_Pixel_Sizes(face, 0, 8);

	int size;
	int code;
	FChar ch;
	for(size=8; size<48; size++){
		for(code='!'; code<256; code++){

			FT_Load_Char(face, code, FT_LOAD_RENDER);

			ch.size = size;
			ch.code = code;
			ch.width = g->bitmap.width;
			ch.height = g->bitmap.rows;
			ch._dataSize = sizeof(char) * ch.width * ch.height;

			fwrite(&ch, sizeof(FChar), 1, fp);
			fwrite(g->bitmap.buffer, ch._dataSize, 1, fp);

		}
	}

	FT_Done_Face(face);
	FT_Done_FreeType(ft);
	

	return 0;
}