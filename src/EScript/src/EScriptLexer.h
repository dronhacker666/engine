#ifndef ESCRIPTLEXER_H
#define ESCRIPTLEXER_H

#include "ELib.h"
#include "EScriptVM.h"
#include "EScriptParser.h"

typedef struct {
	bool (*process) (EArrayInstance_p, EPipelineInstance_p, int);
} _EScriptLexer;
extern _EScriptLexer EScriptLexer;

#endif