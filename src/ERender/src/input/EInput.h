#ifndef EINPUT_H
#define EINPUT_H

#include <windows.h>
#include "ERender.h"

typedef struct {
	void (*init) (void);
	BOOL (*keyPress) (unsigned int);
} _EInput;
extern _EInput EInput;

#endif