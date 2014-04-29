#include "../include/ELib.h"

int eStackTest(){
	int i;
	int result = 0;
	EStack stack = eStack.create(100);
	for(i=0; i<100; i++){
		result += i;
		eStack.push1i(stack, i);
	}
	for(i=0; i<100; i++){
		result -= eStack.pop1i(stack);
	}
	if(result==0){
		return true;
	}else{
		return false;
	}
}