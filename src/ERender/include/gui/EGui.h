#ifndef EGUI_H
#define EGUI_H

#include <stdio.h>
#include <ELib.h>
#include <input/EInput.h>
#include <render/ERenderEvents.h>
#include <render/ERenderShader.h>

typedef struct EGuiManager* EGuiManager_p;

#define _EGuiItemPrototype\
	struct EGuiItem* _next;\
	struct EGuiItem* _prev;\
	GLuint texture;\
	void* buffer;\
	bool hasChanged;\
	int x;\
	int y;\
	int width;\
	int height;\
	int zIndex;\
	bool isHover;\
	bool isFocus;


typedef struct EGuiItem{
	_EGuiItemPrototype;
	// some fields: use in gui elements
} EGuiItem, *EGuiItem_p;

typedef struct EGuiManager{

	int screen_width;
	int screen_height;

	EEventManager_p 				events;
	ERenderShaderManagerInstance_p 	shaderManager;

	GLuint block_VBO;
	GLuint block_VAO;

	EGuiItem_p _head;
	EGuiItem_p _current;
} EGuiManager, *EGuiManager_p;

typedef struct {
	EGuiManager_p 	(*create) 	(void);
	void 			(*render) 	(EGuiManager_p);
	void 			(*addItem) 	(EGuiManager_p, EGuiItem_p);

	void 			(*updateView) 	(EGuiManager_p, EGuiItem_p);
} _EGui;
extern _EGui EGui;

#endif