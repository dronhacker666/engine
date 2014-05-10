#ifndef ESCRIPTVM_H
#define ESCRIPTVM_H

typedef enum {
	PUSH,
	POP,
} EScriptCmdType;

typedef struct {
	enum {
		ESV_FLOAT,
		ESV_INT,
		ESV_POINT,
	} type;
	union {
		int i_value;
		float f_value;
		void* p_value;
	};
} EScriptValue, *EScriptValue_p;

typedef struct {
	EScriptCmdType type;
	EScriptValue value;
} EScriptCmd, *EScriptCmd_p;

typedef struct {
	
} EScriptVMInstance, *EScriptVMInstance_p;

typedef struct {
	EScriptVMInstance_p (*create) (void);
	EScriptVMInstance_p (*exec) (void);
} _EScriptVM;
extern _EScriptVM EScriptVM;

#endif