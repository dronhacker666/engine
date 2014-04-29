#include "../include/ELib.h"

#include <malloc.h>

inline EStack eStackCreate(int depth){
	EStack stack = malloc(sizeof(_EStack));
	if(stack==NULL){
		printf("No memory for stack\n");
		return NULL;
	}
	stack->_head = 0;
	stack->_depth = depth;
	stack->_data = malloc(sizeof(_EStackItem)*(depth+1));
	if(stack->_data==NULL){
		printf("No memory for stack\n");
		return NULL;
	}
	return stack;
}

inline void _eStackCheckForOutOnPush(EStack stack){
	if(stack->_head+1 > stack->_depth){
		printf("Stack out of range\n");
		exit(1);
	}
}
inline void _eStackCheckForOutOnPop(EStack stack){
	if(stack->_head-1 < 0){
		printf("Stack is empty\n");
		exit(1);
	}
}

inline int eStackIsEmpty(EStack stack){
	return stack->_head == 0;
}

inline void eStackPush1i(EStack stack, int value){
	_eStackCheckForOutOnPush(stack);
	stack->_data[++stack->_head].i = value;
}
inline void eStackPush1f(EStack stack, float value){
	_eStackCheckForOutOnPush(stack);
	stack->_data[++stack->_head].f = value;
}
inline void eStackPush1p(EStack stack, void* value){
	_eStackCheckForOutOnPush(stack);
	stack->_data[++stack->_head].p = value;
}

inline int eStackPop1i(EStack stack){
	_eStackCheckForOutOnPop(stack);
	return stack->_data[stack->_head--].i;
}
inline float eStackPop1f(EStack stack){
	_eStackCheckForOutOnPop(stack);
	return stack->_data[stack->_head--].f;
}
inline void* eStackPop1p(EStack stack){
	_eStackCheckForOutOnPop(stack);
	return stack->_data[stack->_head--].p;
}

inline int eStackHead1i(EStack stack){
	return stack->_data[stack->_head].i;
}
inline float eStackHead1f(EStack stack){
	return stack->_data[stack->_head].f;
}
inline void* eStackHead1p(EStack stack){
	return stack->_data[stack->_head].p;
}

_eStack eStack = {
	create: eStackCreate,
	isEmpty: eStackIsEmpty,
	push1i: eStackPush1i,
	push1f: eStackPush1f,
	push1p: eStackPush1p,
	pop1i: eStackPop1i,
	pop1f: eStackPop1f,
	pop1p: eStackPop1p,
	head1i: eStackHead1i,
	head1f: eStackHead1f,
	head1p: eStackHead1p,
};