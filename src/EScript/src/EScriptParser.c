#include "EScriptParser.h"

bool processLexem(EScriptParserInstance_p, EArrayInstance_p, int);


bool is_num(char ch){
	return ch>='0' && ch<='9';
}
bool is_letter(char ch){
	return (ch>='a'&&ch<='z') || (ch>='A'&&ch<='Z') || ch=='_';
}
bool is_separator(char ch){
	return ch==';'||ch=='.'||ch==','||ch==':'||ch=='('||ch==')'||ch=='['||ch==']'||ch=='{'||ch=='}';
}
bool is_empty(char ch){
	return ch=='\t'||ch=='\n'||ch=='\r'||ch==' ';
}
bool is_operator(char ch){
	return ch=='+'||ch=='-'||ch=='*'||ch=='/'||ch=='='||ch=='>'||ch=='<';
}

bool inArray(int value, int array[])
{
	int i = 0;
	while(array[i]){
		if(value==array[i]){
			return true;
		}
		i++;
	}
	return false;
}

EScriptParserState calcState(EScriptParserInstance_p parser, const char ch)
{
	if(is_letter(ch))
	{
		return ESP_STATE_ID;
	}
	if(is_num(ch))
	{
		return ESP_STATE_NUM;
	}
	if(is_operator(ch))
	{
		return ESP_STATE_OPERATOR;
	}
	if(is_separator(ch))
	{
		return ESP_STATE_SEPARATOR;
	}
	if(is_empty(ch))
	{
		return ESP_STATE_SKIP;
	}

	printf("Failed char \"%c\" line %i char %i\n", ch, parser->lineCount, parser->charCount);
	return 	ESP_STATE_FAILED;
}

void processSource(EScriptParserInstance_p parser, EScriptParserState state, const char* start, const char* end)
{
	EScriptLexem lex;
	int length = end-start;

	switch(state){
		case ESP_STATE_ID:
			lex.group = LEX_GROUP_NATIVE;
			if(memcmp("if", start, max(length,2) )==0){
				lex.type = LEX_IF;
			}
			else if(memcmp(start, "else", max(length,4) )==0){
				lex.type = LEX_ELSE;
			}
			else if(memcmp(start, "for", max(length,3) )==0){
				lex.type = LEX_FOR;
			}
			else if(memcmp(start, "while", max(length,5) )==0){
				lex.type = LEX_WHILE;
			}
			else{
				lex.group = LEX_GROUP_ID;
				lex.type = LEX_ID;
				lex.s_value = EMem.alloc(length+1);
				memcpy(lex.s_value, start, length);
				lex.s_value[length] = '\0';
			}
		break;
		case ESP_STATE_NUM:
			lex.group = LEX_GROUP_VALUE;
			lex.type = LEX_NUM;
		break;
		case ESP_STATE_OPERATOR:
			lex.group = LEX_GROUP_OPERATOR;
			if(memcmp(start, "==", max(length,2))==0){
				lex.type = LEX_EQ;
			}
			else if(memcmp(start, ">=", max(length,2))==0){
				lex.type = LEX_GT_EQ;
			}
			else if(memcmp(start, "<=", max(length,2))==0){
				lex.type = LEX_LT_EQ;
			}
			else if(memcmp(start, "!=", max(length,2))==0){
				lex.type = LEX_NOT_EQ;
			}
			else if(memcmp(start, "+=", max(length,2))==0){
				lex.type = LEX_CP_ADD;
			}
			else if(memcmp(start, "-=", max(length,2))==0){
				lex.type = LEX_CP_SUB;
			}
			else if(memcmp(start, "*=", max(length,2))==0){
				lex.type = LEX_CP_MUL;
			}
			else if(memcmp(start, "/=", max(length,2))==0){
				lex.type = LEX_CP_DIV;
			}
			else if(memcmp(start, "++", max(length,2))==0){
				lex.type = LEX_INC;
			}
			else if(memcmp(start, "--", max(length,2))==0){
				lex.type = LEX_DEC;
			}
			else if(memcmp(start, "&&", max(length,2))==0){
				lex.type = LEX_AND;
			}
			else if(memcmp(start, "||", max(length,2))==0){
				lex.type = LEX_OR;
			}
			else if(*start=='+'){
				lex.type = LEX_ADD;
			}
			else if(*start=='-'){
				lex.type = LEX_SUB;
			}
			else if(*start=='*'){
				lex.type = LEX_MUL;
			}
			else if(*start=='/'){
				lex.type = LEX_DIV;
			}
			else if(*start=='='){
				lex.type = LEX_CP;
			}
			else if(*start=='<'){
				lex.type = LEX_LT;
			}
			else if(*start=='>'){
				lex.type = LEX_GT;
			}
			else if(*start=='!'){
				lex.type = LEX_NOT;
			}
		break;
		case ESP_STATE_SEPARATOR:
			lex.group = LEX_GROUP_SEPARATOR;
			if(*start=='\n'){
				lex.type = LEX_NEWLINE;
			}
			else if(*start==','){
				lex.type = LEX_COMMA;
			}
			else if(*start=='.'){
				lex.type = LEX_DOT;
			}
			else if(*start==':'){
				lex.type = LEX_COLON;
			}
			else if(*start==';'){
				lex.type = LEX_SEMICOLON;
			}
			else if(*start=='('){
				lex.type = LEX_BKT_OPEN;
			}
			else if(*start==')'){
				lex.type = LEX_BKT_CLOSE;
			}
			else if(*start=='['){
				lex.type = LEX_SQBKT_OPEN;
			}
			else if(*start==']'){
				lex.type = LEX_SQBKT_CLOSE;
			}
			else if(*start=='{'){
				lex.type = LEX_CURBKT_OPEN;
			}
			else if(*start=='}'){
				lex.type = LEX_CURBKT_CLOSE;
			}
		break;
		default:
			printf("ERROR: unknown esp_state %i\n", start);
			exit(0);
	}

	EPipeline.push(parser->pip, &lex);
}


void* EScriptParser_parse(const char* source)
{
	EScriptParserInstance_p parser = EMem.alloc(sizeof(EScriptParserInstance));
	parser->pip = EPipeline.create(sizeof(EScriptLexem), 5);
	EArrayInstance_p code = EArray.create(sizeof(EScriptCmd));

	parser->lineCount = 1;
	parser->waitLexGroup = (int[]){LEX_GROUP_ID, 0};

	EScriptParserState state = ESP_STATE_SKIP;
	EScriptParserState cur_state;

	// Cursors
	const char* cur = source;
	const char* start = cur;

	while(*cur){

		if(*cur=='\n'){
			parser->charCount=0;
			parser->lineCount++;
		}
		parser->charCount++;

		cur_state = calcState(parser, *cur);

		if( state != cur_state ){
			if(state==ESP_STATE_FAILED){
				return false;
			}
			if(state!=ESP_STATE_SKIP){
				processSource(parser, state, start, cur);
				if(parser->pip->count_filed_items>2){
					processLexem(parser, code, 2);
				}
			}
			start = cur;
			state = cur_state;
		}
		cur++;
	}
	processSource(parser, state, start, cur);
	processLexem(parser, code, 1);
	processLexem(parser, code, 0);

	EPipeline.free(parser->pip);
	EMem.free(parser);

	EScriptCode_p result = EMem.alloc(sizeof(EScriptCode));
	result->code = EArray.getData(code);
	result->code_length = code->length;

	EArray.free(code);

	return result;
}


const char* EScriptParser_getLexemName(EScriptLexemType type)
{
	switch(type){
		case LEX_ID: return "LEX_ID";
		case LEX_NUM: return "LEX_NUM";
		case LEX_STRING: return "LEX_STRING";
		case LEX_NEWLINE: return "LEX_NEWLINE";
		case LEX_COMMA: return "LEX_COMMA";
		case LEX_DOT: return "LEX_DOT";
		case LEX_COLON: return "LEX_COLON";
		case LEX_SEMICOLON: return "LEX_SEMICOLON";
		case LEX_BKT_OPEN: return "LEX_BKT_OPEN";
		case LEX_BKT_CLOSE: return "LEX_BKT_CLOSE";
		case LEX_SQBKT_OPEN: return "LEX_SQBKT_OPEN";
		case LEX_SQBKT_CLOSE: return "LEX_SQBKT_CLOSE";
		case LEX_CURBKT_OPEN: return "LEX_CURBKT_OPEN";
		case LEX_CURBKT_CLOSE: return "LEX_CURBKT_CLOSE";
		case LEX_ADD: return "LEX_ADD";
		case LEX_SUB: return "LEX_SUB";
		case LEX_MUL: return "LEX_MUL";
		case LEX_DIV: return "LEX_DIV";
		case LEX_INC: return "LEX_INC";
		case LEX_DEC: return "LEX_DEC";
		case LEX_CP: return "LEX_CP";
		case LEX_EQ: return "LEX_EQ";
		case LEX_GT: return "LEX_GT";
		case LEX_LT: return "LEX_LT";
		case LEX_GT_EQ: return "LEX_GT_EQ";
		case LEX_LT_EQ: return "LEX_LT_EQ";
		case LEX_NOT_EQ: return "LEX_NOT_EQ";
		case LEX_CP_ADD: return "LEX_CP_ADD";
		case LEX_CP_SUB: return "LEX_CP_SUB";
		case LEX_CP_MUL: return "LEX_CP_MUL";
		case LEX_CP_DIV: return "LEX_CP_DIV";
		case LEX_AND: return "LEX_AND";
		case LEX_OR: return "LEX_OR";
		case LEX_NOT: return "LEX_NOT";
		case LEX_IF: return "LEX_IF";
		case LEX_ELSE: return "LEX_ELSE";
		case LEX_WHILE: return "LEX_WHILE";
		case LEX_FOR: return "LEX_FOR";
		default: return "--UNKNOWN--";
	}
}


_EScriptParser EScriptParser = {
	parse: EScriptParser_parse,
	getLexemName: EScriptParser_getLexemName,
};