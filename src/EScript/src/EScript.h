#ifndef ESCRIPT_H
#define ESCRIPT_H

#include "ELib.h"
#include "EScriptMacro.h"
#include "EScriptParser.h"
#include "EScriptVM.h"

typedef struct {
	EScriptParserInstance_p parser;
	EScriptVMInstance_p vm;
} EScriptInstance, *EScriptInstance_p;

typedef struct {
	EScriptInstance_p (*create) (void);
	bool (*exec) (EScriptInstance_p, const char*);
	bool (*execFile) (const char*);
} _EScript;
extern _EScript EScript;

#endif