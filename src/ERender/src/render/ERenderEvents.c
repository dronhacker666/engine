#include <render/ERenderEvents.h>

EEventManager_p EEvents_create(void)
{
	EEventManager_p manager = EMem.alloc(sizeof(EEventManager));

	return manager;
}

void EEvents_addEvent(EEventManager_p manager, void* _event)
{
	Event_p event = _event;
	EEventListener_p listener = manager->_head;
	while(listener){
		if(listener->type==event->type){
			listener->listener(event, listener->attach);
		}
		listener = listener->_next;
	}
}

void EEvents_addListener(EEventManager_p manager, EventType type, EventListener listener, void* _attach)
{
	EEventListener_p item = EMem.alloc(sizeof(EEventListener));

	item->type = type;
	item->listener = listener;
	item->attach = _attach;

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

void EEvents_removeListener(EEventManager_p manager, EventListener _listener)
{
	EEventListener_p listener = manager->_head;
	while(listener)
	{
		if(listener->listener==_listener)
		{
			if(manager->_head==listener)
			{
				manager->_head = listener->_next;
			}
			if(manager->_current==listener)
			{
				manager->_current = listener->_prev;
			}
			if(listener->_next){
				listener->_next->_prev = listener->_prev;
			}
			if(listener->_prev){
				listener->_prev->_next = listener->_next;
			}

			EMem.free(listener);
			break;
		}
		listener = listener->_next;
	}
}

_EEvents EEvents = {
	create:			EEvents_create,
	addEvent:		EEvents_addEvent,
	addListener:	EEvents_addListener,
	removeListener:	EEvents_removeListener,
};