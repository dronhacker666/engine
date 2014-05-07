#include "EScript.h"

int main(void){

	char source[] = "\
		var_a = 20;\
	";

	EScriptInstance_p script = EScript.create();
	EScript.exec(source);

	return 0;
}