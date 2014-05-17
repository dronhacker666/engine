#ifndef EGUITEXT_H
#define EGUITEXT_H

#include "EGui.h"

typedef struct{
	_EGuiItemPrototype;
	// some fields: use in gui elements
	const char* text;
	unsigned int fontSize;

}EGuiTextInstance, *EGuiTextInstance_p;

typedef struct {
	EGuiTextInstance_p (*create) (void);
	void (*setText) (EGuiTextInstance_p, const char*);
} _EGuiText;
extern _EGuiText EGuiText;

#endif