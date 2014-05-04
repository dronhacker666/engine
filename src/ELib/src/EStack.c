#include "../include/ELib.h"

#include <malloc.h>

inline EStackInstance_p eStackCreate(int depth){
	EStackInstance_p stack = malloc(sizeof(EStackInstance));
	if(stack==NULL){
		printf("No memory for stack\n");
		return NULL;
	}
	stack->_head = 0;
	stack->_depth = depth;
	stack->_data = malloc(sizeof(EStackItem)*(depth+1));
	if(stack->_data==NULL){
		printf("No memory for stack\n");
		return NULL;
	}
	return stack;
}

inline void _eStackCheckForOutOnPush(EStackInstance_p stack){
	if(stack->_head+1 > stack->_depth){
		printf("Stack out of range\n");
		exit(1);
	}
}
inline void _eStackCheckForOutOnPop(EStackInstance_p stack){
	if(stack->_head-1 < 0){
		printf("Stack is empty\n");
		exit(1);
	}
}

inline int eStackIsEmpty(EStackInstance_p stack){
	return stack->_head == 0;
}

inline void eStackPush1i(EStackInstance_p stack, int value){
	_eStackCheckForOutOnPush(stack);
	stack->_data[++stack->_head].i = value;
}
inline void eStackPush1f(EStackInstance_p stack, float value){
	_eStackCheckForOutOnPush(stack);
	stack->_data[++stack->_head].f = value;
}
inline void eStackPush1p(EStackInstance_p stack, void* value){
	_eStackCheckForOutOnPush(stack);
	stack->_data[++stack->_head].p = value;
}

inline int eStackPop1i(EStackInstance_p stack){
	_eStackCheckForOutOnPop(stack);
	return stack->_data[stack->_head--].i;
}
inline float eStackPop1f(EStackInstance_p stack){
	_eStackCheckForOutOnPop(stack);
	return stack->_data[stack->_head--].f;
}
inline void* eStackPop1p(EStackInstance_p stack){
	_eStackCheckForOutOnPop(stack);
	return stack->_data[stack->_head--].p;
}

inline int eStackHead1i(EStackInstance_p stack){
	return stack->_data[stack->_head].i;
}
inline float eStackHead1f(EStackInstance_p stack){
	return stack->_data[stack->_head].f;
}
inline void* eStackHead1p(EStackInstance_p stack){
	return stack->_data[stack->_head].p;
}

_EStack EStack = {
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