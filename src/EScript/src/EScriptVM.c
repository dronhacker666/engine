#include "EScriptVM.h"

EScriptVMInstance_p EScriptVM_create(void)
{
	EScriptVMInstance_p vm = EMem.alloc(sizeof(EScriptVMInstance));

	return vm;
}

const char* EScriptVM_toString(EScriptCmd_p cmd)
{
	char buffer[1024];
	switch(cmd->type){
		case CMD_FOCUS: sprintf(buffer, "CMD_FOCUS %s", cmd->value.s_value); break;
		case CMD_VALUE: sprintf(buffer, "CMD_VALUE %f", cmd->value.f_value); break;
		default: sprintf(buffer, "--UNKNOWN--"); break;
	}
	return buffer;
}


_EScriptVM EScriptVM = {
	create: EScriptVM_create,

	toString: EScriptVM_toString,
};