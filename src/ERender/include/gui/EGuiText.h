#ifndef EGUITEXT_H
#define EGUITEXT_H

#include "EGui.h"

typedef struct{
	_EGuiItemPrototype;
	// some fields: use in gui elements
	const wchar_t* text;
	int fontSize;
}EGuiTextInstance, *EGuiTextInstance_p;

typedef struct {
	EGuiTextInstance_p (*create) (void);
	void (*setText) (EGuiTextInstance_p, const wchar_t*);
} _EGuiText;
extern _EGuiText EGuiText;

#endif