#ifndef EINPUT_H
#define EINPUT_H

#include <windows.h>
#include "ERenderEvents.h"

typedef struct {
	EventPrototype;
	unsigned int 	keyCode;
} KeyboardEvent, *KeyboardEvent_p;

typedef struct {
	EventPrototype;
	unsigned int 	x;
	unsigned int 	y;
	unsigned int 	dx;
	unsigned int 	dy;
	unsigned int 	lbutton;
	unsigned int 	rbutton;
	unsigned int 	mbutton;
	int 			wheel;
} MouseEvent, *MouseEvent_p;

typedef struct {
	void (*init) (void);
	BOOL (*keyPress) (unsigned int);
} _EInput;
extern _EInput EInput;

#endif