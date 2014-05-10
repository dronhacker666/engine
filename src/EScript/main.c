#include "EScript.h"

int main(void){

	char source[] = "a= 10; b= a + 20;";

	EScriptInstance_p scope = EScript.create();
	EScript.exec(scope, source);

	EMem.printUsage();

	return 0;
}