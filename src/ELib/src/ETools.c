#include "../include/ELib.h"

unsigned int ETools_hashString(const char* str){
	unsigned int hash = 0;
	for(; *str; str++)
		hash = (hash * 1664525) + (unsigned char)(*str) + 1013904223;
	return hash;
}

bool ETools_loadFile(const char* filename, char** content, int* length)
{
	FILE* fp = fopen(filename, "rb");
	int size;
	if(fp==NULL){
		printf("ERROR: LoadFile('%s', ..., ...) - cannot read this file\n", filename);
		return false;
	}else{
		fseek(fp, 0, SEEK_END);
		size = ftell(fp);
		rewind(fp);
		*content = EMem.alloc( sizeof(char)*size );
		if(*content==NULL){
			printf("%s\n", "No memory");
			return false;
		}
		fread(*content, sizeof(char)*size , 1, fp);

		(*content)[size] = '\0';
		*length = size;
		fclose(fp);
	}
	return true;
}


_ETools ETools = {
	hashString: ETools_hashString,
	loadFile: ETools_loadFile,
};
