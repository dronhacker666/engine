#ifndef ESCRIPTMACRO_H
#define ESCRIPTMACRO_H

#include <malloc.h>
#include <mem.h>
#include <stdio.h>

#define new(NAME,TYPE)\
	TYPE##_p NAME = malloc(sizeof(TYPE));\
	if( NAME==NULL ){\
		printf("ERROR: malloc error in \"%s\" line %i\n", __FILE__, __LINE__);\
		exit(1);\
	}\
	memset(NAME, 0, sizeof(TYPE));

#endif