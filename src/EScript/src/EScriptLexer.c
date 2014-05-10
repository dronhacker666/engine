#include "EScriptLexer.h"

EScriptLexemGroup beforeLexGroup = LEX_GROUP_UNDEFINED;

bool process(EArrayInstance_p code, EScriptLexem_p lex, EPipelineInstance_p pip, int offset)
{
	EScriptCmd cmd;

	printf("%s\n", EScriptParser.getLexemName(lex->type) );

	return true;
}


bool EScriptLexer_process(EArrayInstance_p code, EPipelineInstance_p pip, int offset)
{
	EScriptLexem_p lex = EPipeline.get(pip, offset);
	if(! process(code, lex, pip, offset) ){
		return false;
	}
	beforeLexGroup = lex->group;
	return true;
}

_EScriptLexer EScriptLexer = {
	process: EScriptLexer_process,
};