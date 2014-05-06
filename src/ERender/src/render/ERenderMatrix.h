#ifndef ERENDERMATRIX_H
#define ERENDERMATRIX_H

#include <math.h>

typedef float Matrix4f[16];

typedef struct {
	void (*perspective4f)	(Matrix4f M, float fovy, float aspect, float znear, float zfar);
	void (*ortho4f)			(Matrix4f, float, float, float, float);
	void (*rotation4f)		(Matrix4f M, float x, float y, float z);
	void (*translation4f)	(Matrix4f M, float x, float y, float z);
	void (*mul4f)			(Matrix4f M, Matrix4f A, Matrix4f B);
} _ERenderMatrix;
extern _ERenderMatrix ERenderMatrix;

#endif