#include "../include/ELib.h"

unsigned int eToolsHashString(char* str){
	unsigned int res = 0;
	while(*str){
		res = (res<<5) + res + *str++;
	}
	return res;
}

bool eToolsLoadFile(char* filename, char** content, int* length)
{
	FILE* fp = fopen(filename, "rb+");
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

		(*content)[size] = 0;
		*length = size;
		fclose(fp);
	}
	return true;
}


_eTools eTools = {
	hashString: eToolsHashString,
	loadFile: eToolsLoadFile,
};
