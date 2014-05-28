#ifndef EGUIBUTTON_H
#define EGUIBUTTON_H

#include "EGui.h"

typedef struct{
	_EGuiItemPrototype;
	// some fields: use in gui elements
}EGuiButtonInstance, *EGuiButtonInstance_p;

typedef struct {
	EGuiButtonInstance_p (*create) (void);
} _EGuiButton;
extern _EGuiButton EGuiButton;

#endif