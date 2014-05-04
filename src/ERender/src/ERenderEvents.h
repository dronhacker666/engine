#ifndef ERENDEREVENTS_H
#define ERENDEREVENTS_H

typedef enum 
{
	// Render
	beforeRender,
	afterRender,

	// Mouse
	mouseDown
	mouseUp
	mouseMove

	// Keyboard
	keyDown
	keyUp

} EventType;

typedef void(*EventListener)(void*);

typedef struct {
	EventType type;
	EventListener listener;

	void* _next;
	void* _prev;
} EEventListener, *EEventListener_p;

typedef struct {
	EEventListener_p _head;
	EEventListener_p _current;
} EEventManager, *EEventManager_p;

typedef struct {
	EEventManager_p		(*create)		(void);
	void 				(*addEvent)		(EEventManager_p, EventType, void*);
	void 				(*addListener)	(EEventManager_p, EventType, EventListener);
} _EEvents;
extern _EEvents EEvents;

#endif