#ifndef elbib_h
#define elbib_h

/**
*	INCLUDES
*/
#include <stdio.h>
#include <mem.h>
#include <malloc.h>

/**
*	Base Types
**/
typedef enum {false, true} bool;


/**
*	Memory
*/
typedef struct
{
	void* (*alloc) (unsigned int);
	void* (*clone) (const void*, unsigned int);
	void (*free) (void*);

	void (*printUsage) (void);
} _EMem;
extern _EMem EMem;


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
* Pipeline
*/
typedef struct {
	void* _data;
	int length;
	int count_filed_items;
	int pos;
	int item_size;
} EPipelineInstance, *EPipelineInstance_p;

typedef struct {
	EPipelineInstance_p 	(*create) 	(const int, const int);
	void 					(*free) 	(EPipelineInstance_p);
	void 					(*push) 	(EPipelineInstance_p, const void*);
	void* 					(*get) 		(EPipelineInstance_p, int);
} _EPipeline;
extern _EPipeline EPipeline;

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
} EArrayInstance, *EArrayInstance_p;

typedef struct {
	EArrayInstance_p 	(*create)	(int);
	void 				(*free)		(EArrayInstance_p);
	void*				(*getData)	(EArrayInstance_p);
	int 				(*push)		(EArrayInstance_p, void*);
	void 				(*reset)	(EArrayInstance_p);
	void* 				(*next)		(EArrayInstance_p);
	void* 				(*get)		(EArrayInstance_p, int);
} _EArray;
extern _EArray EArray;

/**
* Hash
*/
typedef enum{
	HashItem_point,
	HashItem_int,
	HashItem_float,
	HashItem_string,
} EHashItemType;

#define HASHITEMID 0x1234567
typedef struct EHashItem {
	int __id__;
	unsigned int hash;
	EHashItemType type;
	const char* key;

	union{
		void* p_value;
		char* s_value;
		int i_value;
		float f_value;
	};

	struct EHashItem* _prev;
	struct EHashItem* _next;
} EHashItem, *EHashItem_p;

#define HASHINSTANCEID 0x93867737
typedef struct {
	int __id__;
	EHashItem_p _head;
	EHashItem_p _current;
	unsigned int length;
} EHashInstance, *EHashInstance_p;

typedef struct {
	EHashInstance_p 	(*create)	(void);
	void 				(*delete) 	(EHashInstance_p, const char*);
	void 				(*free) 	(EHashInstance_p);
	void 				(*rfree) 	(EHashInstance_p);
	bool 				(*typeIs) 	(EHashInstance_p, const char*, EHashItemType);

	EHashItem_p 		(*get) 		(EHashInstance_p, const char*);
	bool 				(*has) 		(EHashInstance_p, const char*);

	void 				(*set1p) 	(EHashInstance_p, const char*, void*);
	void*				(*get1p) 	(EHashInstance_p, const char*);

	void 				(*set1i) 	(EHashInstance_p, const char*, int);
	int					(*get1i) 	(EHashInstance_p, const char*);

	void 				(*set1f) 	(EHashInstance_p, const char*, float);
	float				(*get1f) 	(EHashInstance_p, const char*);

	void 				(*set1s) 	(EHashInstance_p, const char*, char*, size_t);
	char*				(*get1s) 	(EHashInstance_p, const char*);

	void				(*dump)		(EHashInstance_p);

} _EHash;
extern _EHash EHash;


/**
*	Linked List
*/
typedef struct EListItem {
	struct EListItem* prev;
	struct EListItem* next;
	void* data;
} EListItem, *EListItem_p;

typedef struct {
	EListItem_p head;
	EListItem_p last;
	unsigned int length;
} EListInstance, *EListInstance_p;

typedef struct {
	EListInstance_p (*create) (void);
	void (*push) (EListInstance_p, void*);
	void (*insertAfter) (EListInstance_p, void*, unsigned int);

	void (*remove) (EListInstance_p, unsigned int);
	void (*free) (EListInstance_p);

	void* (*get) (EListInstance_p, unsigned int);
} _EList;
extern _EList EList;

/**
*	Tools
*/

typedef struct {
	char* content;
	unsigned int length;
	bool success;
} FileResult;

typedef struct {
	unsigned int 	(*hashString)	(const char *);
	bool	 		(*loadFile)		(const char*, char**, int*);
} _ETools;
extern _ETools ETools;

#endif