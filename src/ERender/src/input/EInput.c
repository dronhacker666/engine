#include <input/EInput.h>

void EInput_proccessInput(void)
{

}

void EInput_init(void)
{
	//EEvents.addListener(render->events, &onMouseMove);
}

BOOL EInput_keyPress(unsigned int keyCode)
{
	return GetAsyncKeyState(keyCode);
}

_EInput EInput = {
	init: 		EInput_init,
	keyPress: 	EInput_keyPress,
};