#ifndef ESCRIPTPARSER_H
#define ESCRIPTPARSER_H

#include "ELib.h"

enum {

	LEX_ID,
	LEX_NUM,
	LEX_STRING,

	LEX_NEWLINE, // \n
	LEX_COMMA, // ,
	LEX_DOT, // .
	LEX_COLON, // :
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

typedef struct {
	bool (*parse) (EArrayInstance_p, const char*);
} _EScriptParser;
extern _EScriptParser EScriptParser;

#endif