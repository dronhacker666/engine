#include "libfont.h"
#include "headers.h"
#include "ELib.h"

typedef struct
{
	unsigned int width;
	unsigned int height;
	int top;
	int left;
	unsigned char* buffer;
} LFChar;


EHashInstance_p cache = NULL;
LFChar* charset = NULL;
unsigned char fontSize;

void Libfont_init(void)
{
	if(!cache){
		cache = EHash.create();
	}
}

void Libfont_free(void)
{
	EHash.free(cache);
}

void* Libfont_loadFont(const char* filename, unsigned char fontSize)
{
	LFChar* result;
	FChar fchar;
	FCharset charset;
	FILE* fp = fopen(filename, "rb");
	if(!fp){
		printf("File \"%s\" can't open\n", filename);
		return NULL;
	}

	while(!feof(fp))
	{
		fread(&charset, sizeof(charset), 1, fp);
		if(charset.fontSize == fontSize){
			break;
		}else{
			fseek(fp, charset._dataSize, SEEK_CUR);
		}
	}

	int i;
	result = malloc(sizeof(LFChar)*128);
	for(i=0; i<127; i++)
	{
		fread(&fchar, sizeof(FChar), 1, fp);
		result[i].width = fchar.width;
		result[i].height = fchar.height;
		result[i].top = fchar.top;
		result[i].left = fchar.left;
		result[i].buffer = malloc(fchar._dataSize);
		fread(result[i].buffer, fchar._dataSize, 1, fp);
	}

	fclose(fp);
	return result;
}

int Libfont_setFont(const char* filename, unsigned char _fontSize)
{
	char fullname[1024];
	sprintf(fullname, "%s_%u", filename, _fontSize);

	if(EHash.has(cache, fullname)){
		charset = EHash.get1p(cache, fullname);
	}else{
		charset = Libfont_loadFont(filename, _fontSize);
		if(charset){
			EHash.set1p(cache, fullname, charset);
		}else{
			return 0;
		}
	}

	fontSize = _fontSize;

	return 1;
}

/*
	for(y=0; y<height; y++){
		for(x=0; x<width; x++){
			printf("%c", ((unsigned char*)out)[y*width+x] > 128 ? 'x' : ' ' );
		}
		printf("\n");
	}
*/


void Libfont_genText(void* out, const char* text, unsigned int width, unsigned int height)
{
	int x, y;
	const char* cur = text;
	LFChar ch;

	int cx = 0;
	int cy = 0;

	int buffer_size = sizeof(char)*width*height;

	while(*cur)
	{
		switch(*cur){
			case ' ':
				cx += (int)fontSize/2;
			break;
			case '\n':
				cx = 0;
				cy += fontSize;
			break;
			default:
				ch = charset[*cur];
				for(y=0; y<ch.height; y++){
					for(x=0; x<ch.width; x++){
						int offset = (cy+y+(fontSize-ch.top))*width+x+cx;
						if(offset < buffer_size){
							((unsigned char*)out)[offset] = ch.buffer[y*ch.width+x];
						}
					}
				}
				cx += ch.width - ch.left;
		}
		cur++;
	}
}

_Libfont Libfont = {
	init: Libfont_init,
	free: Libfont_free,
	setFont: Libfont_setFont,
	genText: Libfont_genText,
};