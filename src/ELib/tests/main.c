#include "../include/ELib.h"

#define CHECK(TEST)\
	if( TEST() ){\
		testOk(#TEST);\
	}else{\
		testFailed(#TEST);\
		return 1;\
	}

void testFailed(char* testName){
	printf("Test FAILED %s:\n", testName);
}
void testOk(char* testName){
	printf("Test OK     %s\n", testName);
}

int main(void){

	printf("%i\n", eTools.hashString("some string"));

	CHECK(eStackTest);

	return 0;
}