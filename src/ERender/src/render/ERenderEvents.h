#ifndef ERENDEREVENTS_H
#define ERENDEREVENTS_H

#include "ERenderMacro.h"

typedef enum 
{
	// Render
	beforeRender,
	afterRender,

	// Mouse
	mouseDown,
	mouseUp,
	mouseMove,

	// Keyboard
	keyDown,
	keyUp,

} EventType;

// Events

typedef struct {
	EventType type;
} Event, *Event_p;

typedef struct {
	EventType type;
} RenderEvent, *RenderEvent_p;

typedef struct {
	EventType 		type;
	unsigned int 	keyCode;
} KeyboardEvent, *KeyboardEvent_p;

typedef struct {
	EventType 		type;
	unsigned int 	x;
	unsigned int 	y;
	unsigned int 	dx;
	unsigned int 	dy;
	unsigned int 	lbutton;
	unsigned int 	rbutton;
	unsigned int 	mbutton;
	int 			wheel;
} MouseEvent, *MouseEvent_p;

//-------------------------------------

typedef void(*EventListener)(Event_p);

typedef struct EEventListener{
	EventType type;
	EventListener listener;

	struct EEventListener* _next;
	struct EEventListener* _prev;
} EEventListener, *EEventListener_p;

typedef struct {
	EEventListener_p _head;
	EEventListener_p _current;
} EEventManager, *EEventManager_p;

typedef struct {
	EEventManager_p		(*create)			(void);
	void 				(*addEvent)			(EEventManager_p, void*);
	void 				(*addListener)		(EEventManager_p, EventType, EventListener);
	void 				(*removeListener)	(EEventManager_p, EventListener);
} _EEvents;
extern _EEvents EEvents;

#endif