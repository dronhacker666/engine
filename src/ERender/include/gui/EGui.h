#ifndef EGUI_H
#define EGUI_H

#include <stdio.h>

#include <ELib.h>
#include <ERenderAPI.h>

typedef struct EGuiManager* EGuiManager_p;

#define _EGuiItemPrototype\
	struct EGuiItem* _next;\
	struct EGuiItem* _prev;\
	void(*render)(void*, EGuiManager_p);\
	int x, y, zIndex, width, height, rotate;


typedef struct EGuiItem{
	_EGuiItemPrototype;
	// some fields: use in gui elements
} EGuiItem, *EGuiItem_p;

typedef struct EGuiManager{
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