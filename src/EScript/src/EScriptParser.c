#include "EScriptParser.h"


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


typedef enum{
	ESP_STATE_FAILED,
	ESP_STATE_ID,
	ESP_STATE_NUM,
	ESP_STATE_STRING,
	ESP_STATE_SEPARATOR,
	ESP_STATE_OPERATOR,
	ESP_STATE_SKIP,
} EScriptParserState;


int lineCount=1;
int charCount=0;
EPipelineInstance_p pip;

EScriptParserState calcState(const char ch)
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

	printf("Failed char \"%c\" line %i char %i\n", ch, lineCount, charCount);
	return 	ESP_STATE_FAILED;
}

void processLexem(EScriptParserState state, const char* start, const char* end)
{
	EScriptLexem lex;

	switch(state){
		case ESP_STATE_ID:
			lex.group = LEX_GROUP_NATIVE;
			if(memcmp(start, "if", end-start)==0){
				lex.type = LEX_IF;
			}
			else if(memcmp(start, "else", end-start)==0){
				lex.type = LEX_ELSE;
			}
			else if(memcmp(start, "for", end-start)==0){
				lex.type = LEX_FOR;
			}
			else if(memcmp(start, "while", end-start)==0){
				lex.type = LEX_WHILE;
			}
			else{
				lex.group = LEX_GROUP_ID;
				lex.type = LEX_ID;
			}
		break;
		case ESP_STATE_NUM:
			lex.group = LEX_GROUP_VALUE;
			lex.type = LEX_NUM;
		break;
		case ESP_STATE_OPERATOR:
			lex.group = LEX_GROUP_OPERATOR;
			if(memcmp(start, "==", 2)){
				lex.type = LEX_EQ;
			}
			else if(memcmp(start, ">=", 2)){
				lex.type = LEX_GT_EQ;
			}
			else if(memcmp(start, "<=", 2)){
				lex.type = LEX_LT_EQ;
			}
			else if(memcmp(start, "!=", 2)){
				lex.type = LEX_NOT_EQ;
			}
			else if(memcmp(start, "+=", 2)){
				lex.type = LEX_CP_ADD;
			}
			else if(memcmp(start, "-=", 2)){
				lex.type = LEX_CP_SUB;
			}
			else if(memcmp(start, "*=", 2)){
				lex.type = LEX_CP_MUL;
			}
			else if(memcmp(start, "/=", 2)){
				lex.type = LEX_CP_DIV;
			}
			else if(memcmp(start, "++", 2)){
				lex.type = LEX_INC;
			}
			else if(memcmp(start, "--", 2)){
				lex.type = LEX_DEC;
			}
			else if(memcmp(start, "&&", 2)){
				lex.type = LEX_AND;
			}
			else if(memcmp(start, "||", 2)){
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

	EPipeline.push(pip, &lex);
}

void processCode(int offset)
{
	EScriptLexem_p lex = EPipeline.get(pip, offset);

	printf("%i\n", lex->type);

}

bool EScriptParser_parse(EArrayInstance_p out, const char* source)
{
	EScriptParserState state = ESP_STATE_SKIP;
	EScriptParserState cur_state;

	// Cursors
	const char* cur = source;
	const char* start = cur;

	pip = EPipeline.create(sizeof(EScriptLexem), 5);

	while(*cur){

		if(*cur=='\n'){
			charCount=0;
			lineCount++;
		}
		charCount++;

		cur_state = calcState(*cur);

		if( state != cur_state ){
			if(state==ESP_STATE_FAILED){
				return false;
			}
			if(state!=ESP_STATE_SKIP){
				processLexem(state, start, cur-1);
				if(pip->count_filed_items>2){
					processCode(2);
				}
			}
			start = cur;
			state = cur_state;
		}
		cur++;
	}
	processCode(1);
	processCode(0);

	return true;
}

_EScriptParser EScriptParser = {
	parse: EScriptParser_parse,
};