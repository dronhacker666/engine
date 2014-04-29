#include "../include/ELib.h"


unsigned int eToolsHashString(char* str){
	unsigned int res = 0;
	while(*str){
		res = (res<<5) + res + *str++;
	}
	return res;
}

_eTools eTools = {
	hashString: eToolsHashString
};
