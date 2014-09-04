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
	EHashInstance_p hash = EMem.alloc(sizeof(EHashInstance));

	hash->__id__ = HASHINSTANCEID;

	return hash;
}

void EHash_delete(EHashInstance_p hash, const char* key)
{

}

void EHash_free(EHashInstance_p hash)
{
	void* p;
	EHashItem_p item = hash->_head;
	while(item){
		p = item;
		item = item->_next;
		EMem.free(p);
	}
	EMem.free(hash);
}
void EHash_rfree(EHashInstance_p hash)
{
	void* p;
	EHashItem_p item = hash->_head;
	while(item){
		if(
			item->type == HashItem_point &&
			((EHashInstance_p)item->p_value)->__id__ == HASHINSTANCEID
		){
			EHash_rfree(item->p_value);
		}
		p = item;
		item = item->_next;
		EMem.free(p);
	}
	EMem.free(hash);
}

bool EHash_typeIs(EHashInstance_p hash, const char* key, EHashItemType type)
{

}

EHashItem_p EHash_createItem(EHashInstance_p hash, const char* key)
{
	EHashItem_p item = EMem.alloc(sizeof(EHashItem));

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
	item->key = EMem.clone(key, strlen(key)+1);

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

bool EHash_has(EHashInstance_p hash, const char* key)
{
	return EHash_get(hash, key) != NULL;
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


void EHash_set1s(EHashInstance_p hash, const char* key, char* value, size_t length)
{
	if(!length){
		length = strlen(value);
	}
	char* mem = EMem.alloc(length);
	memcpy(mem, value, length);
	mem[length] = '\0';
	EHashItem_p item = EHash_createItem(hash, key);
	item->type = HashItem_string;
	item->s_value = mem;
}
char* EHash_get1s(EHashInstance_p hash, const char* key)
{
	EHashItem_p item = EHash_get(hash, key);
	return item->s_value;
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


void EHash_set1f(EHashInstance_p hash, const char* key, float value)
{
	EHashItem_p item = EHash_createItem(hash, key);
	item->type = HashItem_float;
	item->f_value = value;
}
float EHash_get1f(EHashInstance_p hash, const char* key)
{
	EHashItem_p item = EHash_get(hash, key);
	return item->f_value;
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
				printf("%s(float): %f\n", item->key, item->f_value);
			break;
			case HashItem_string:
				printf("%s(string): \"%s\"\n", item->key, item->s_value);
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
	delete: EHash_delete,
	free: EHash_free,
	rfree: EHash_rfree,
	typeIs: EHash_typeIs,

	get:	EHash_get,
	has:	EHash_has,

	set1p: EHash_set1p,
	get1p: EHash_get1p,

	set1i: EHash_set1i,
	get1i: EHash_get1i,

	set1f: EHash_set1f,
	get1f: EHash_get1f,

	set1s: EHash_set1s,
	get1s: EHash_get1s,

	dump: EHash_dump,
};