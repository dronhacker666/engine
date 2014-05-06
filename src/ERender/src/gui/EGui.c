#include "EGui.h"

EGuiManager_p EGui_create(void)
{
	EGuiManager_p manager = malloc(sizeof(EGuiManager));
	memset(manager, 0, sizeof(EGuiManager));
	return manager;
}

void EGui_addItem(EGuiManager_p manager, EGuiItem_p item)
{
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


void EGui_render(EGuiManager_p manager)
{
	EGuiItem_p item = manager->_head;
	while(item){
		item->render(item);
		item = item->_next;
	}
}


_EGui EGui = {
	create: EGui_create,
	render: EGui_render,
	addItem: EGui_addItem,
};
