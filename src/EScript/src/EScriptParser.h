#ifndef ESCRIPTPARSER_H
#define ESCRIPTPARSER_H

#include "ELib.h"
#include "EScriptVM.h"
#include "EScriptMacro.h"

typedef enum {
	LEX_GROUP_UNDEFINED,
	LEX_GROUP_ID,
	LEX_GROUP_VALUE,
	LEX_GROUP_NATIVE,
	LEX_GROUP_OPERATOR,
	LEX_GROUP_SEPARATOR,
} EScriptLexemGroup;

typedef enum {
	LEX_ID,
	LEX_NUM,
	LEX_STRING,

	LEX_NEWLINE, // \n
	LEX_COMMA, // ,
	LEX_DOT, // .
	LEX_COLON, // :
	LEX_SEMICOLON, // ;
	LEX_BKT_OPEN, // (
	LEX_BKT_CLOSE, // )
	LEX_SQBKT_OPEN, // [
	LEX_SQBKT_CLOSE, // ]
	LEX_CURBKT_OPEN, // {
	LEX_CURBKT_CLOSE, // }

	LEX_ADD, // +
	LEX_SUB, // -
	LEX_MUL, // *
	LEX_DIV, // /

	LEX_INC, // ++
	LEX_DEC, // --

	LEX_CP, // =
	LEX_EQ, // ==
	LEX_GT, // >
	LEX_LT, // <
	LEX_GT_EQ, // >=
	LEX_LT_EQ, // <=
	LEX_NOT_EQ, // !=

	LEX_CP_ADD, // +=
	LEX_CP_SUB, // -=
	LEX_CP_MUL, // *=
	LEX_CP_DIV, // /=

	LEX_AND, // &&
	LEX_OR, // ||
	LEX_NOT, // !

	LEX_IF,
	LEX_ELSE,
	LEX_WHILE,
	LEX_FOR,
} EScriptLexemType;

typedef enum{
	ESP_STATE_SKIP,
	ESP_STATE_FAILED,
	ESP_STATE_ID,
	ESP_STATE_NUM,
	ESP_STATE_STRING,
	ESP_STATE_SEPARATOR,
	ESP_STATE_OPERATOR,
} EScriptParserState;

typedef struct {
	EScriptLexemGroup group;
	EScriptLexemType type;
	union{
		int i_value;
		float f_value;
		char* s_value;
	};
} EScriptLexem, *EScriptLexem_p;

typedef struct {

	// parser part
	int lineCount;
	int charCount;
	EPipelineInstance_p pip;

	// lexer part
	int *waitLexGroup;
	EStackInstance_p id_stack;
	EStackInstance_p bkt_stack;

} EScriptParserInstance, *EScriptParserInstance_p;

typedef struct {
	EScriptParserInstance_p 	(*create) 			(void);
	bool 						(*parse) 			(EScriptParserInstance_p, EArrayInstance_p, const char*);
	const char* 				(*getLexemName) 	(EScriptLexemType);
} _EScriptParser;
extern _EScriptParser EScriptParser;

#endif