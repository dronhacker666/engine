#ifndef ESCRIPT_H
#define ESCRIPT_H

#include "ELib.h"
#include "EScriptMacro.h"

typedef struct {
	int some;
} EScriptInstance, *EScriptInstance_p;

typedef struct {
	EScriptInstance_p (*create) (void);
	bool (*exec) (const char*);
	bool (*execFile) (const char*);
} _EScript;
extern _EScript EScript;

#endif