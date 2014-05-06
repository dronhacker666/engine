#ifndef EGUI_H
#define EGUI_H

#include <malloc.h>
#include <mem.h>
#include "ERenderMacro.h"
#include "EGuiMacro.h"

typedef struct EGuiItem{
	_EGuiItemPrototype;
	// some fields: use in gui elements
} EGuiItem, *EGuiItem_p;

typedef struct {
	EGuiItem_p _head;
	EGuiItem_p _current;
} EGuiManager, *EGuiManager_p;

typedef struct {
	EGuiManager_p 	(*create) 	(void);
	void 			(*render) 	(EGuiManager_p);
	void 			(*addItem) 	(EGuiManager_p, EGuiItem_p);
} _EGui;
extern _EGui EGui;

//WIDGETS
#include "EGuiText.h"

#endif