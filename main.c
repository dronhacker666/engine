#include "include/engine.h"

int main(void){
	lua_State *L=luaL_newstate();
	luaL_openlibs(L);

	luaL_dofile(L,"mylua.lua");

	lua_close(L);
	return 0;
}

