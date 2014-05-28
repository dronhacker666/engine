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

bool loadJPEG(const char*, Image_p);
bool loadTGA(const char*, Image_p);

#endif