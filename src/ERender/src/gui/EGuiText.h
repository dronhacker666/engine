#ifndef EGUITEXT_H
#define EGUITEXT_H

#include "EGui.h"

typedef struct {
	// class required fields. Show EGui.h
	void* _next;
	void* _prev;
	void(*render)(void);
	// some fields: use in gui elements

	int x;
	int y;
	char* text;
	unsigned int fontSize;

} EGuiTextInstance, *EGuiTextInstance_p;

typedef struct {
	EGuiTextInstance_p (*create) (char* text);
} _EGuiText;
extern _EGuiText EGuiText;

#endif