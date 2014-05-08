#include "EScript.h"

int main(void){

	char source[] = "\
		var_a = 20;\n\
		var_b = var_a + 10;\n\
	";

	EScriptInstance_p scope = EScript.create();
	EScript.exec(scope, source);

	return 0;
}