#ifndef LIBFONT_H
#define LIBFONT_H

#include <stdio.h>
#include <malloc.h>

typedef struct
{
	void (*init) (void);
	void (*free) (void);
	int (*setFont) (const char*, unsigned char);
	void (*genText) (void*, const wchar_t*, unsigned int, unsigned int);
} _Libfont;
extern _Libfont Libfont;

#endif