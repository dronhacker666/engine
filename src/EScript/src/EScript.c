#include "EScript.h"

EScriptInstance_p EScript_create(void)
{
	new(script, EScriptInstance);
}

bool EScript_exec(const char* source)
{

}

_EScript EScript = {
	create: EScript_create,
	exec: EScript_exec,
};