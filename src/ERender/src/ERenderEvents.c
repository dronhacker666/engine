#include "ERenderEvents.h"
#include <malloc.h>
#include <mem.h>
#include <stdio.h>

EEventManager_p EEvents_create(void)
{
	EEventManager_p manager = malloc(sizeof(EEventManager));
	manager->_head = NULL;
	manager->_current = NULL;
	return manager;
}

void EEvents_addEvent(EEventManager_p manager, EventType type, void* data)
{
	EEventListener_p listener = manager->_head;
	while(listener){
		if(listener->type==type){
			listener->listener(data);
		}
		listener = listener->_next;
	}
}

void EEvents_addListener(EEventManager_p manager, EventType type, EventListener listener)
{
	EEventListener_p item = malloc(sizeof(EEventListener));
	item->type = type;
	item->listener = listener;
	item->_next = NULL;
	item->_prev = manager->_current;

	if(manager->_head==NULL){
		manager->_head = item;
	}
	if(manager->_current!=NULL){
		manager->_current->_next = item;
	}
	manager->_current = item;
}

_EEvents EEvents = {
	create:			EEvents_create,
	addEvent:		EEvents_addEvent,
	addListener:	EEvents_addListener,
};