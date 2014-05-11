#include "EScript.h"

EScriptInstance_p EScript_create(void)
{
	EScriptInstance_p script = EMem.alloc(sizeof(EScriptInstance));
	script->parser = EScriptParser.create();
	script->vm = EScriptVM.create();
	return script;
}

bool EScript_exec(EScriptInstance_p scope, const char* source)
{
	EArrayInstance_p code = EArray.create(sizeof(EScriptCmd));
	EScriptParser.parse(scope->parser, code, source);

}

_EScript EScript = {
	create: EScript_create,
	exec: EScript_exec,
};