#ifndef ERENDEREVENTS_H
#define ERENDEREVENTS_H

#include <ELib.h>

typedef enum 
{
	// Render
	beforeRender,
	afterRender,

	// Mouse
	mouseMove,
	mouseDown,
	mouseUp,

	// Keyboard
	keyPress,
	keyDown,
	keyUp,

} EventType;

// Events

#define EventPrototype\
	EventType type;

typedef struct {
	EventPrototype;
} Event, *Event_p;

//-------------------------------------

typedef void(*EventListener)(Event_p, void*);

typedef struct EEventListener{
	EventType type;
	EventListener listener;
	void* attach;

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
	void 				(*addListener)		(EEventManager_p, EventType, EventListener, void*);
	void 				(*removeListener)	(EEventManager_p, EventListener);
} _EEvents;
extern _EEvents EEvents;

#endif