#ifndef ERENDERMATH_H
#define ERENDERMATH_H

typedef struct {
	float x;
	float y;
	float z;
} Vec3f, *Vec3f_p;

typedef struct {
	void 	(*direction3f) 	(Vec3f_p, Vec3f_p, Vec3f_p);
	float 	(*length3f)		(Vec3f_p);
	void 	(*normalize3f)	(Vec3f_p);
} _Vec;
extern _Vec Vec;

#endif