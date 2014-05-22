#include "ERenderMath.h"
#include <math.h>

float Vec_length3f(Vec3f_p v)
{
	return sqrt(v->x*v->x + v->y*v->y + v->z*v->z);
}

void Vec_normalize3f(Vec3f_p v){
	float l = Vec_length3f(v);
	v->x /= l;
	v->y /= l;
	v->z /= l;
}

void Vec_direction3f(Vec3f_p out, Vec3f_p v1, Vec3f_p v2)
{
	out->x = v2->x - v1->x;
	out->y = v2->y - v1->y;
	out->z = v2->z - v1->z;
	Vec_normalize3f(out);
}

_Vec Vec = {
	direction3f: Vec_direction3f,
	normalize3f: Vec_normalize3f,
	length3f: Vec_length3f,
};