#include <input/EInput.h>
#include <render/ERender.h>
#include <time.h>

BYTE keyboardState[256];
POINT mouseState;
int timer = 0;

void EInput_updateInput(RenderEvent_p event, void* attach)
{
	KeyboardEvent keyEvent;
	MouseEvent mouseEvent;
	memset(&mouseEvent, 0, sizeof(MouseEvent));
	wchar_t ch = 0;
	int keyCode;
	BYTE ks[256];

	GetKeyboardState(ks);

	mouseEvent.x = mouseState.x;
	mouseEvent.y = mouseState.y;
	GetCursorPos(&mouseState);
	mouseEvent.dx =  mouseState.x - mouseEvent.x;
	mouseEvent.dy = mouseState.y - mouseEvent.y;
	mouseEvent.x = mouseState.x;
	mouseEvent.y = mouseState.y;

	mouseEvent.lbtn = keyboardState[1];
	mouseEvent.rbtn = keyboardState[2];
	mouseEvent.mbtn = keyboardState[4];

	for(keyCode=0; keyCode<256; keyCode++){

		ToUnicode(keyCode, 0, ks, &ch, sizeof(wchar_t), 0);
		keyEvent.keyCode = keyCode;
		keyEvent.charCode = ch;

		if(keyboardState[keyCode] != ks[keyCode]){

			if(keyCode<5){ // mouse btns
				if(keyboardState[keyCode] & 0x80){ // UP
					mouseEvent.type = mouseUp;
				}else{ // DOWN
					mouseEvent.type = mouseDown;
				}
				EEvents.addEvent(event->render->events, &mouseEvent);
			}else{
				if(keyboardState[keyCode] & 0x80){ // UP
					keyEvent.type = keyUp;
					EEvents.addEvent(event->render->events, &keyEvent);
				}else{ // DOWN
					keyEvent.type = keyDown;
					EEvents.addEvent(event->render->events, &keyEvent);
					keyEvent.type = keyPress;
					EEvents.addEvent(event->render->events, &keyEvent);
				}
			}

			timer = clock() + 500;

			keyboardState[keyCode] = ks[keyCode];
		}
	}

	if(clock()>timer){
		for(keyCode=0; keyCode<256; keyCode++){
			if(keyboardState[keyCode] & 0x80){
				ToUnicode(keyCode, 0, ks, &ch, sizeof(wchar_t), 0);
				keyEvent.keyCode = keyCode;
				keyEvent.charCode = ch;
				keyEvent.type = keyPress;
				EEvents.addEvent(event->render->events, &keyEvent);
			}
		}
		timer = clock()+30;
	}

	if(mouseEvent.dx || mouseEvent.dy){
		mouseEvent.type = mouseMove;
		EEvents.addEvent(event->render->events, &mouseEvent);
	}

}

void EInput_init(EEventManager_p eventManager)
{
	GetKeyboardState(keyboardState);
	EEvents.addListener(eventManager, beforeRender, (void*)EInput_updateInput, NULL);
}

bool EInput_keyPress(unsigned int keyCode)
{
	return keyboardState[keyCode] & 0x80;
}

_EInput EInput = {
	init: 		EInput_init,
	keyPress: 	EInput_keyPress,
};