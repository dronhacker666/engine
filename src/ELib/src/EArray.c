#include "../include/ELib.h"

#include <stdlib.h>
#include <mem.h>

EArray eArrayCreate(int item_size){
	EArray array = malloc(sizeof(_EArray));
	array->_item_size = item_size;
	array->_alloc = 0;
	array->length = 0;
	array->current = 0;
	return array;
}

int eArrayPush(EArray array, void *data){
	if(array->length >= array->_alloc){
		array->_alloc += ARRAY_PART_COUNT;
		void* newMemory = malloc(array->_item_size*array->_alloc);
		if(array->length>0){
			memcpy(newMemory, array->_data, array->_item_size*array->length);
			free(array->_data);
		}
		array->_data = newMemory;
	}
	memcpy( array->_data +(array->_item_size*array->length++), data, array->_item_size);
	return array->length-1;
}

void eArrayReset(EArray array){
	array->current = 0;
}

void* eArrayNext(EArray array){
	if(array->current < array->length){
		return array->_data + (array->_item_size*array->current++);
	}else{
		return 0;
	}
}

void* eArrayGet(EArray array, int index){
	return array->_data + (index*array->_item_size);
}

void eArrayFree(EArray array){
	if(array->length>0){
		free(array->_data);
	}
	free(array);
}


_eArray eArray = {
	create: eArrayCreate,
	free: eArrayFree,
	push: eArrayPush,
	reset: eArrayReset,
	next: eArrayNext,
	get: eArrayGet,
};