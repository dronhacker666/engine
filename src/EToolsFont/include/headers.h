#ifndef HEADERS_H
#define HEADERS_H

typedef struct
{
	unsigned char fontSize;
	unsigned int _dataSize;
} FCharset;

typedef struct
{
	int code;
	unsigned int width;
	unsigned int height;
	int top;
	int left;
	unsigned int _dataSize;
} FChar;

#endif