#include "ELib.h"

unsigned int HashLy(const char * str)
{
	unsigned int hash = 0;
	for(; *str; str++)
		hash = (hash * 1664525) + (unsigned char)(*str) + 1013904223;
	return hash;
}


EHashInstance_p EHash_create(void)
{
	EHashInstance_p hash = malloc(sizeof(EHashInstance));
	memset(hash, 0, sizeof(EHashInstance));

	hash->__id__ = HASHINSTANCEID;

	return hash;
}

void EHash_remove(EHashInstance_p hash, const char* key)
{

}

bool EHash_typeIs(EHashInstance_p hash, const char* key, EHashItemType type)
{

}

EHashItem_p EHash_createItem(EHashInstance_p hash, const char* key)
{
	EHashItem_p item = malloc(sizeof(EHashItem));
	memset(item, 0, sizeof(EHashItem));

	// Link
	if(hash->_head==NULL){
		hash->_head = item;
	}
	if(hash->_current){
		hash->_current->_next = item;
	}
	item->_next = NULL;
	item->_prev = hash->_current;
	hash->_current = item;

	item->__id__ = HASHITEMID;
	item->hash = HashLy(key);

	// Key
	item->key = key;

	return item;
}

EHashItem_p EHash_get(EHashInstance_p hash, const char* key)
{
	unsigned int hashed_key = HashLy(key);
	EHashItem_p item = hash->_head;
	while(item){
		if(item->hash==hashed_key){
			return item;
		}
		item = item->_next;
	}
	return NULL;
}


void EHash_set1p(EHashInstance_p hash, const char* key, void* value)
{
	EHashItem_p item = EHash_createItem(hash, key);
	item->type = HashItem_point;
	item->p_value = value;
}
void* EHash_get1p(EHashInstance_p hash, const char* key)
{
	EHashItem_p item = EHash_get(hash, key);
	return item->p_value;
}


void EHash_set1i(EHashInstance_p hash, const char* key, int value)
{
	EHashItem_p item = EHash_createItem(hash, key);
	item->type = HashItem_int;
	item->i_value = value;
}
int EHash_get1i(EHashInstance_p hash, const char* key)
{
	EHashItem_p item = EHash_get(hash, key);
	return item->i_value;
}

int __EHash_dump_tab=0;
void EHash_dump(EHashInstance_p hash){
	__EHash_dump_tab++;
	EHashItem_p item = hash->_head;
	printf("{\n");
	while(item){
		int i=0;for(;i<__EHash_dump_tab;i++){printf("\t");}

		switch(item->type){
			case HashItem_point:
				if( ((EHashInstance_p)item->p_value)->__id__ == HASHINSTANCEID ){
					printf("%s(hash): ", item->key);
					EHash_dump(item->p_value);
				}else{
					printf("%s(point): %i\n", item->key, item->p_value);
				}
			break;
			case HashItem_int:
				printf("%s(int): %i\n", item->key, item->i_value);
			break;
			case HashItem_float:
				printf("%s(float): %i\n", item->key, item->f_value);
			break;
		}

		item = item->_next;
	}

	__EHash_dump_tab--;
	int i=0;for(;i<__EHash_dump_tab;i++){printf("\t");}
	printf("}\n");
}

_EHash EHash = {
	create: EHash_create,
	remove: EHash_remove,
	typeIs: EHash_typeIs,

	get:	EHash_get,

	set1p: EHash_set1p,
	get1p: EHash_get1p,

	set1i: EHash_set1i,
	get1i: EHash_get1i,

	dump: EHash_dump,
};