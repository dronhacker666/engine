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

int main(void)
{
	int a;
	EPipelineInstance_p pip = EPipeline.create(sizeof(int), 3);
	a= 10; EPipeline.push(pip, &a);
	a= 20; EPipeline.push(pip, &a);
	a= 30; EPipeline.push(pip, &a);
	a= 40; EPipeline.push(pip, &a);
	a= 50; EPipeline.push(pip, &a);


	printf("%i\n", *(int*)EPipeline.get(pip,0) );
	printf("%i\n", *(int*)EPipeline.get(pip,1) );
	printf("%i\n", *(int*)EPipeline.get(pip,2) );
	printf("%i\n", *(int*)EPipeline.get(pip,3) );
	printf("%i\n", *(int*)EPipeline.get(pip,4) );


	printf("%i\n", eTools.hashString("some string"));

	CHECK(eStackTest);
	CHECK(eHashTest);

	char* content;
	int length;
	if(eTools.loadFile("bin/testfile", &content, &length)){
		printf("%s \nlength %i\n", content, length);
	}

	EMem.printUsage();

	return 0;
}