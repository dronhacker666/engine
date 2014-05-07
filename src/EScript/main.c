#include "EScript.h"

int main(void){

	char source[] = "\
		var_a = 20;\
	";

	EScriptInstance_p scope = EScript.create();
	EScript.exec(scope, source);

	return 0;
}