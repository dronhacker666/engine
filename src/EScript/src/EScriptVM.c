#include "EScriptVM.h"

EScriptVMInstance_p EScriptVM_create(void)
{
	EScriptVMInstance_p vm = EMem.alloc(sizeof(EScriptVMInstance));

	return vm;
}

void EScriptVM_exec(EScriptVMInstance_p vm, const EScriptCode_p data)
{

}

void EScriptVM_toString(EScriptCmd_p cmd)
{
	switch(cmd->type){
		case CMD_PUSH_LVALUE: printf("CMD_PUSH_LVALUE %s\n", cmd->value.s_value); break;
		case CMD_VALUE: printf("CMD_VALUE %f\n", cmd->value.f_value); break;
		default: printf("--UNKNOWN--\n"); break;
	}
}

void EScriptVM_dump(EScriptCode_p data)
{
	unsigned int i;
	EScriptCmd_p cmd;
	for(i=0; i<data->code_length; i++){
		EScriptVM_toString( &data->code[i] );
	}
}

_EScriptVM EScriptVM = {
	create: EScriptVM_create,
	exec: EScriptVM_exec,
	dump: EScriptVM_dump,
};