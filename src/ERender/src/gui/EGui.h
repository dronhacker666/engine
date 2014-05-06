#ifndef EGUI_H
#define EGUI_H

#include <mem.h>
#include <malloc.h>
#include <stdio.h>
#include "ERenderAPI.h"
#include "ERenderMacro.h"
#include "EGuiMacro.h"

#define _EGuiItemPrototype\
	struct EGuiItem* _next;\
	struct EGuiItem* _prev;\
	void(*render)(void*);\
	int x, y, zIndex, width, heigth, rotate;


typedef struct EGuiItem{
	_EGuiItemPrototype;
	// some fields: use in gui elements
} EGuiItem, *EGuiItem_p;

typedef struct {
	ERenderShaderManagerInstance_p shaderManager;

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
#include "EGuiButton.h"

#endif