#include "../include/ELib.h"

#include <stdlib.h>
#include <mem.h>

EArrayInstance_p EArray_create(int item_size){
	EArrayInstance_p array = EMem.alloc(sizeof(EArrayInstance));
	array->_item_size = item_size;
	array->_alloc = 0;
	array->length = 0;
	array->current = 0;
	return array;
}

int EArray_push(EArrayInstance_p array, void *data){
	if(array->length >= array->_alloc){
		array->_alloc += ARRAY_PART_COUNT;
		void* newMemory = EMem.alloc(array->_item_size*array->_alloc);
		if(array->length>0){
			memcpy(newMemory, array->_data, array->_item_size*array->length);
			EMem.free(array->_data);
		}
		array->_data = newMemory;
	}
	memcpy( array->_data +(array->_item_size*array->length++), data, array->_item_size);
	return array->length-1;
}

void EArray_reset(EArrayInstance_p array){
	array->current = 0;
}

void* EArray_next(EArrayInstance_p array){
	if(array->current < array->length){
		return array->_data + (array->_item_size*array->current++);
	}else{
		return 0;
	}
}

void* EArray_get(EArrayInstance_p array, int index){
	return array->_data + (index*array->_item_size);
}

void EArray_free(EArrayInstance_p array){
	if(array->length>0){
		EMem.free(array->_data);
	}
	EMem.free(array);
}


_EArray EArray = {
	create: EArray_create,
	free: EArray_free,
	push: EArray_push,
	reset: EArray_reset,
	next: EArray_next,
	get: EArray_get,
};