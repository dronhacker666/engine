#ifndef ESYS_H
#define ESYS_H

typedef struct {
	int (*getCoreAmount) (void);
} _ESys;
extern _ESys ESys;


void asyncLoadFile(const char*, void (*) (void*));

#endif