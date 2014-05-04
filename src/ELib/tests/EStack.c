#include "../include/ELib.h"

int eStackTest(){
	int i;
	int result = 0;
	EStackInstance_p stack = EStack.create(100);
	for(i=0; i<100; i++){
		result += i;
		EStack.push1i(stack, i);
	}
	for(i=0; i<100; i++){
		result -= EStack.pop1i(stack);
	}
	if(result==0){
		return true;
	}else{
		return false;
	}
}