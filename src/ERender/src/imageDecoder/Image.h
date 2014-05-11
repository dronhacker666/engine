#ifndef IMAGE_H
#define IMAGE_H

typedef struct {
	int width;
	int height;
	int depth;
	enum{
		RGB,
		BGR,
	} colorSpace;
	void* data;
} Image, *Image_p;

#endif