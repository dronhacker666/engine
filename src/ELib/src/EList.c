#include "ELib.h"

EListInstance_p EList_create(void)
{
	EListInstance_p list = EMem.alloc(sizeof(EListInstance));
	return list;
}

EListItem_p EList_getItem(EListInstance_p list, unsigned int index)
{
	if(index>list->length){
		printf("EList error: request to bad index %i\n", index);
		exit(0);
	}

	EListItem_p cur = list->head;
	while(cur && index){
		index--;
		cur = cur->next;
	}
	return index==0 ? cur : NULL;
}

void EList_insertAfter(EListInstance_p list, void* data, unsigned int index)
{
	EListItem_p item = EMem.alloc(sizeof(EListItem));
	item->data = data;

	EListItem_p place = EList_getItem(list, index);
	if(!place){
		item->prev = NULL;
		if(list->head){
			list->head->prev = item;
			item->next = list->head;
		}
		list->head = item;
	}else{
		if(place == list->last){
			list->last = item;
		}else{
			place->next->prev = item;
			item->next = place->next;
		}
		item->prev = place;
		place->next = item;
	}
	list->length++;
}

void EList_push(EListInstance_p list, void* data)
{
	EListItem_p item = EMem.alloc(sizeof(EListItem));
	item->data = data;

	if(list->head==NULL){
		list->head = item;
	}
	if(list->last){
		list->last->next = item;
	}
	item->next = NULL;
	item->prev = list->last;
	list->last = item;

	list->length++;
}

void EList_remove(EListInstance_p list, unsigned int index)
{

}

void EList_free(EListInstance_p list)
{

}

void* EList_get(EListInstance_p list, unsigned int index)
{
	return EList_getItem(list, index)->data;
}

_EList EList = {
	create: EList_create,
	push: EList_push,
	insertAfter: EList_insertAfter,
	remove: EList_remove,
	free: EList_free,
	get: EList_get,
};