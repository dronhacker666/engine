#include "EScript.h"

int main(void){

	char source[] = "a= 10; b= a + 20;";

	EScriptCode_p code = EScriptParser.parse(source);

	EScriptVMInstance_p vm = EScriptVM.create();
	EScriptVM.dump(code);

	//EScriptVM.exec(vm, code);

	EMem.printUsage();

	return 0;
}