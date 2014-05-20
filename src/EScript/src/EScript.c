#include "EScript.h"

EScriptInstance_p EScript_create(void)
{

}

bool EScript_exec(EScriptInstance_p scope, const char* source)
{


}

_EScript EScript = {
	create: EScript_create,
	exec: EScript_exec,
};