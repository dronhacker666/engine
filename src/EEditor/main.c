#include <ERenderAPI.h>

int main(void)
{
	ERenderInstance_p render = ERender.create(800, 600);

	EGuiTextInstance_p wcmd = EGuiText.create();
	wcmd->fontSize = 10;
	wcmd->x = 10;
	wcmd->y = 220;
	wcmd->width = 700;
	wcmd->height = 100;

	EGui.addItem(render->gui, (EGuiItem_p)wcmd);

	EGuiText.setText(wcmd, L"Hello World");

	while(render->enabled){
		ERender.render(render);
	}

	EMem.printUsage();

	return 0;
}