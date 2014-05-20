#include "EScriptVM.h"
#include "EScriptParser.h"

bool processLexem(EScriptParserInstance_p parser, EArrayInstance_p code, int offset)
{
	EScriptCmd cmd;
	EScriptLexem_p lex = EPipeline.get(parser->pip, offset);

	printf("--%s\n", EScriptParser.getLexemName(lex->type) );

	switch(lex->group)
	{
		case LEX_GROUP_ID:
			if(lex->type==LEX_ID){
				cmd.type = CMD_PUSH_LVALUE;
				cmd.value.type = ESV_STRING;
				cmd.value.s_value = lex->s_value;
			}
		break;
		case LEX_GROUP_VALUE:

		break;
		case LEX_GROUP_NATIVE:

		break;
		case LEX_GROUP_OPERATOR:

		break;
		case LEX_GROUP_SEPARATOR:

		break;
	}




	EArray.push(code, &cmd);

	return true;
}
