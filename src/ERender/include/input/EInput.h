#ifndef EINPUT_H
#define EINPUT_H

#include <stdint.h>
#include <render/ERenderEvents.h>

typedef struct {
	EventPrototype;
	unsigned int 	keyCode;
	unsigned int 	charCode;
} KeyboardEvent, *KeyboardEvent_p;

typedef struct {
	EventPrototype;
	int 	x;
	int 	y;
	int 	dx;
	int 	dy;
	int 	lbtn;
	int 	rbtn;
	int 	mbtn;
	int 	wheel;
} MouseEvent, *MouseEvent_p;


typedef struct {
	void (*init) (EEventManager_p);
	bool (*keyPress) (unsigned int);
} _EInput;
extern _EInput EInput;

#endif