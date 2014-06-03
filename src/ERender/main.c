#include <ERenderAPI.h>
#include <windows.h>
#include <time.h>
#include <wchar.h>

ERenderInstance_p render;

EGuiTextInstance_p wcmd;
wchar_t buff[1024];
int buff_pos = 0;

void onKeyPress(KeyboardEvent_p event)
{
	switch(event->keyCode){
		case 13:
			buff[buff_pos] = '\n';
			buff_pos++;
		break;
		case 8:
			buff_pos--;
			buff_pos = buff_pos<0 ? 0 : buff_pos;
		break;
		default:
			if(event->charCode){
				buff[buff_pos] = event->charCode;
				buff_pos++;
			}
	}
	buff[buff_pos] = '_';
	buff[buff_pos+1] = '\0';

	EGuiText.setText(wcmd, buff);
}

void onBeforeRender(RenderEvent_p event)
{
	if(EInput.keyPress('W')){
		render->camera->position.x -= sin(M_PI/180 * render->camera->rotation.y) * 0.1 * render->timerFix;
		render->camera->position.y += sin(M_PI/180 * render->camera->rotation.x) * 0.1 * render->timerFix;
		render->camera->position.z += cos(M_PI/180 * render->camera->rotation.y) * 0.1 * render->timerFix;
	}
	if(EInput.keyPress('S')){
		render->camera->position.x += sin(M_PI/180 * render->camera->rotation.y) * 0.1 * render->timerFix;
		render->camera->position.y -= sin(M_PI/180 * render->camera->rotation.x) * 0.1 * render->timerFix;
		render->camera->position.z -= cos(M_PI/180 * render->camera->rotation.y) * 0.1 * render->timerFix;
	}
	if(EInput.keyPress('D')){
		render->camera->position.x -= sin(M_PI/180 * (render->camera->rotation.y+90)) * 0.1 * render->timerFix;
		//render->camera->position.y += sin(M_PI/180 * render->camera->rotation.x) * 0.1 * render->timerFix;
		render->camera->position.z += cos(M_PI/180 * (render->camera->rotation.y+90)) * 0.1 * render->timerFix;
	}
	if(EInput.keyPress('A')){
		render->camera->position.x -= sin(M_PI/180 * (render->camera->rotation.y-90)) * 0.1 * render->timerFix;
		//render->camera->position.y += sin(M_PI/180 * render->camera->rotation.x) * 0.1 * render->timerFix;
		render->camera->position.z += cos(M_PI/180 * (render->camera->rotation.y-90)) * 0.1 * render->timerFix;
	}
}

void onMouseMove(MouseEvent_p event)
{
	if(event->lbtn){
		render->camera->rotation.x += (float)event->dy;
		render->camera->rotation.y += (float)event->dx;
	}
}
void onMouseDown(MouseEvent_p event)
{
	EEvents.addListener(render->events, mouseMove, (void*)onMouseMove);
}
void onMouseUp(MouseEvent_p event)
{
	EEvents.removeListener(render->events, (void*)onMouseMove);
}


void cback(void* data)
{
	printf("%s\n", (char*)data);
}


int main(void)
{
	/*wchar_t* c = L"а привет";

	printf("%X \n", *c);

	exit(0);*/

	printf("Core amount: %i\n", ESys.getCoreAmount());

	//asyncLoadFile("../data/model.obj", &cback);

	/*pthread_t thread;
	if (pthread_create(&thread, NULL, thread_func, NULL) != 0){
		return 1;
	}
	if (pthread_join(thread, NULL) != 0){
		return 1;
	}
	*/

	render = ERender.create(800, 600);

	ERenderScene.load(render->scene, "../data/model.obj");
	ERenderObjectInstance_p beretta = ERenderScene.load(render->scene, "../data/beretta.obj");

	beretta->position.y = 4;


	wcmd = EGuiText.create();
	EGuiTextInstance_p wfps = EGuiText.create();
	EGui.addItem(render->gui, (EGuiItem_p)wcmd);
	EGui.addItem(render->gui, (EGuiItem_p)wfps);

	wfps->x = 10;
	wfps->y = 10;
	wfps->width = 200;
	wfps->height = 100;

	wcmd->fontSize = 10;
	wcmd->x = 10;
	wcmd->y = 220;
	wcmd->width = 700;
	wcmd->height = 100;

	EEvents.addListener(render->events, keyPress, (void*)onKeyPress);
	EEvents.addListener(render->events, beforeRender, (void*)onBeforeRender);


	EEvents.addListener(render->events, mouseDown, (void*)onMouseDown);
	EEvents.addListener(render->events, mouseUp, (void*)onMouseUp);


	int fps = 0;
	int s = clock();

	wchar_t fps_buffer[100];

	while(render->enabled){

		beretta->rotation.y += 1.0 * render->timerFix;


		ERender.render(render);


		fps++;
		if(clock()-s>1000){

			wsprintf(fps_buffer, L"fps:%i\nsize:%ix%i\n", fps, render->width, render->height);
			EGuiText.setText(wfps, fps_buffer);

			render->timerFix = 60.0f/(float)fps;

			s = clock();
			fps = 0;
		}
	}


	EMem.printUsage();

	return 0;
}