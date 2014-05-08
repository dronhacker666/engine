#include "EScript.h"

EScriptInstance_p EScript_create(void)
{
	new(script, EScriptInstance);
}

bool EScript_exec(EScriptInstance_p scope, const char* source)
{
	EArrayInstance_p lexems = EArray.create(sizeof(EScriptLexem));
	EScriptParser.parse(lexems, source);

}

_EScript EScript = {
	create: EScript_create,
	exec: EScript_exec,
};