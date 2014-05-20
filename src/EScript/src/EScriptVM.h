#ifndef ESCRIPTVM_H
#define ESCRIPTVM_H

#include "ELib.h"

typedef enum {
	CMD_PUSH_LVALUE,
	CMD_PUSH_RVALUE,
	CMD_VALUE,

} EScriptCmdType;

typedef struct {
	enum {
		ESV_NULL,
		ESV_FLOAT,
		ESV_INT,
		ESV_POINT,
		ESV_STRING,
	} type;
	union {
		int i_value;
		float f_value;
		void* p_value;
		char* s_value;
	};
} EScriptValue, *EScriptValue_p;

typedef struct {
	EScriptCmdType type;
	EScriptValue value;
} EScriptCmd, *EScriptCmd_p;


typedef struct {
	EScriptCmd_p code;
	unsigned int code_length;
} EScriptCode, *EScriptCode_p;


typedef struct {
	
} EScriptVMInstance, *EScriptVMInstance_p;

typedef struct {
	EScriptVMInstance_p (*create) 		(void);
	void				(*exec) 		(EScriptVMInstance_p, const EScriptCode_p);
	void				(*dump) 		(EScriptCode_p);
} _EScriptVM;
extern _EScriptVM EScriptVM;

#endif