#include "include/ERenderAPI.h"
#include <windows.h>

ERenderInstance_p render;

int main(void)
{
	ERenderCreateOptions renderOptions = {
		width: 800,
		height: 600,
	};
	render = ERender.create(&renderOptions);

	ERenderShaderInstance_p fshader = ERenderShader.create("data\\test.fs");

	while(!GetAsyncKeyState(VK_ESCAPE)){


		ERender.render(render);
	}

	return 0;
}