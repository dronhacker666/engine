#ifndef EGUITEXTFIELD_H
#define EGUITEXTFIELD_H

#include "EGui.h"
#include "EGuiText.h"

typedef struct{
	_EGuiItemPrototype;
	// some fields: use in gui elements
	int cursor;
	const wchar_t* value;
	EGuiTextInstance_p _text_widget;
}EGuiTextFieldInstance, *EGuiTextFieldInstance_p;

typedef struct {
	EGuiTextFieldInstance_p (*create) (void);
} _EGuiTextField;
extern _EGuiTextField EGuiTextField;

#endif