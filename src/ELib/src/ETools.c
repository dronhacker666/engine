#include "../include/ELib.h"
#include <malloc.h>

unsigned int eToolsHashString(char* str){
	unsigned int res = 0;
	while(*str){
		res = (res<<5) + res + *str++;
	}
	return res;
}

FileResult eToolsLoadFile(const char* filename)
{
	FileResult res = {success:true};
	FILE* fp = fopen (filename, "rb+");
	if(fp==NULL){
		res.success = false;
		printf("ERROR: LoadFile('%s', ..., ...) - cannot read this file\n", filename);
	}else{
		fseek(fp, 0, SEEK_END);
		res.length = ftell(fp);
		rewind(fp);
		res.content = (char*)malloc( sizeof(char)*res.length );
		if(res.content==NULL){
			printf("%s\n", "No memory");
			res.success = false;
		}
		fread(res.content, sizeof(char) , res.length, fp);
		res.content[res.length] = 0;
		fclose(fp);
	}
	return res;
}


_eTools eTools = {
	hashString: eToolsHashString,
	loadFile: eToolsLoadFile,
};
