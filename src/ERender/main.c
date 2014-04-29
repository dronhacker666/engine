#include "include/ERender.h"
#include <windows.h>

ERenderHandler render;

int main(void)
{
	ERenderCreateOptions renderOptions = {
		width: 800,
		height: 600,
	};
	render = ERender.create(&renderOptions);

	while(!GetAsyncKeyState(VK_ESCAPE)){


		ERender.render();
	}

	return 0;
}