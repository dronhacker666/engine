#ifndef EGUITEXT_H
#define EGUITEXT_H

#include "EGui.h"

typedef struct{
	_EGuiItemPrototype;
	// some fields: use in gui elements
	char* text;
	unsigned int fontSize;

}EGuiTextInstance, *EGuiTextInstance_p;

typedef struct {
	EGuiTextInstance_p (*create) (char* text);
} _EGuiText;
extern _EGuiText EGuiText;

#endif