#ifndef elbib_h
#define elbib_h

/**
*	INCLUDES
*/
#include <stdio.h>
#include <malloc.h>

/**
*	Base Types
**/
typedef int bool;
#define true 1
#define false 0


/**
*	Stack		
*/
typedef union{
	int i;
	float f;
	void* p;
} EStackItem;

typedef struct{
	int _head;
	int _depth;
	EStackItem* _data;
} EStackInstance, *EStackInstance_p;

typedef struct {
	EStackInstance_p 	(*create)	(int);
	int 				(*isEmpty)	(EStackInstance_p);
	void 				(*push1i)	(EStackInstance_p, int);
	void 				(*push1f)	(EStackInstance_p, float);
	void 				(*push1p)	(EStackInstance_p, void*);
	int 				(*pop1i)	(EStackInstance_p);
	float 				(*pop1f)	(EStackInstance_p);
	void* 				(*pop1p)	(EStackInstance_p);
	int 				(*head1i)	(EStackInstance_p);
	float 				(*head1f)	(EStackInstance_p);
	void* 				(*head1p)	(EStackInstance_p);
} _EStack;
extern _EStack EStack;


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
	char* content;
	unsigned int length;
	bool success;
} FileResult;

typedef struct {
	unsigned int 	(*hashString)	(char *);
	bool	 		(*loadFile)		(char*, char**, int*);
} _eTools;
extern _eTools eTools;

#endif