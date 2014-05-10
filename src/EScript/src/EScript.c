#include "EScript.h"

EScriptInstance_p EScript_create(void)
{
	EScriptInstance_p script = EMem.alloc(sizeof(EScriptInstance));
	return script;
}

bool EScript_exec(EScriptInstance_p scope, const char* source)
{
	EArrayInstance_p code = EArray.create(sizeof(EScriptCmd));
	EScriptParser.parse(code, source);

}

_EScript EScript = {
	create: EScript_create,
	exec: EScript_exec,
};