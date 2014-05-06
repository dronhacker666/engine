#ifndef EGUIMACRO_H
#define EGUIMACRO_H

#define _EGuiItemPrototype\
	struct EGuiItem* _next;\
	struct EGuiItem* _prev;\
	void(*render)(void*);\
	int x, y, zIndex, width, heigth, rx, ry, rz;

#endif