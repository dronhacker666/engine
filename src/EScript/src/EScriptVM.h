#ifndef ESCRIPTVM_H
#define ESCRIPTVM_H

typedef enum {
	PUSH,
} EScriptCmdType;

typedef struct {
	EScriptCmdType type;
} EScriptCmd, *EScriptCmd_p;

typedef struct {
	
} EScriptVMInstance, *EScriptVMInstance_p;

typedef struct {
	EScriptVMInstance_p (*create) (void);
	EScriptVMInstance_p (*exec) (void);
} _EScriptVM;
extern _EScriptVM EScriptVM;

#endif