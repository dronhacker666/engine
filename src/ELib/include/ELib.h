#ifndef elbib_h
#define elbib_h

/**
*	INCLUDES
*/
#include <stdio.h>

/**
*	Base Types
**/
#define bool int
#define true 1
#define false 0


/**
*	Stack		
*/
typedef union{
	int i;
	float f;
	void* p;
} _EStackItem;

typedef struct{
	int _head;
	int _depth;
	_EStackItem* _data;
} _EStack, *EStack;

typedef struct {
	EStack 	(*create)	(int);
	int 	(*isEmpty)	(EStack);
	void 	(*push1i)	(EStack, int);
	void 	(*push1f)	(EStack, float);
	void 	(*push1p)	(EStack, void*);
	int 	(*pop1i)	(EStack);
	float 	(*pop1f)	(EStack);
	void* 	(*pop1p)	(EStack);
	int 	(*head1i)	(EStack);
	float 	(*head1f)	(EStack);
	void* 	(*head1p)	(EStack);
} _eStack;
extern _eStack eStack;


/**
*	Array
*/
#define ARRAY_PART_COUNT 100

typedef struct {
	int length;
	void* _data;
	int current;
	int _alloc;
	int _item_size;
} _EArray;
typedef _EArray *EArray;

typedef struct {
	EArray 	(*create)	(int);
	void 	(*free)		(EArray);
	int 	(*push)		(EArray, void*);
	void 	(*reset)	(EArray);
	void* 	(*next)		(EArray);
	void* 	(*get)		(EArray, int);
} _eArray;
extern _eArray eArray;


/**
*	Tools
*/
typedef struct {
	unsigned int (*hashString)(char *);
} _eTools;
extern _eTools eTools;

#endif