#include "include/ERender.h"

ERenderHandler render;

int main(void)
{
	ERenderCreateOptions renderOptions = {
		width: 800,
		height: 600,
	};
	render = ERender.create(&renderOptions);

	ERender.render();

	return 0;
}