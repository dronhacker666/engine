#include "ELib.h"

unsigned int memoryAlloc = 0;

void* EMem_alloc(unsigned int size)
{
	void* memory = malloc(size);
	if(!memory){
		printf("EMem error: failed alloc memory\n");
		exit(1);
	}
	memset(memory, 0, size);
	memoryAlloc += size;
	return memory;
}

void* EMem_clone(const void* ptr, unsigned int size)
{
	void* memory = malloc(size);
	if(!memory){
		printf("EMem error: failed alloc memory\n");
		exit(1);
	}
	memcpy(memory, ptr, size);
	memoryAlloc += size;
	return memory;
}

void EMem_free(void* ptr)
{
	free(ptr);
}

void EMem_printUsage(void)
{
	char *sizes[] = { "%0.0fB", "%0.2fKB", "%0.2fMB", "%0.2fGB" };
	double len = memoryAlloc;
	int order = 0;
	while (len >= 1024 && order + 1 < sizeof(sizes)) {
		order++;
		len = len/1024;
	}
	printf("Memory alloc: ");
	printf(sizes[order], len);
	printf("\n");
}


_EMem EMem = {
	alloc: EMem_alloc,
	clone: EMem_clone,
	free: EMem_free,
	printUsage: EMem_printUsage,
};