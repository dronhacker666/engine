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
	char str1[] = "str1";
	char str2[] = "str2";
	char str3[] = "str3";

	EListInstance_p list = EList.create();
	EList.push(list, str1);
	EList.push(list, str2);
	EList.push(list, str3);


	printf("%s\n", (char*)EList.get(list, 0));
	printf("%s\n", EList.get(list, 1));
	printf("%s\n", EList.get(list, 2));

	exit(0);

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


	printf("%i\n", ETools.hashString("some string"));

	CHECK(eStackTest);
	CHECK(eHashTest);


	EMem.printUsage();

	return 0;
}