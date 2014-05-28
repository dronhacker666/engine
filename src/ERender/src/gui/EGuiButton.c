#include <gui/EGuiButton.h>

void EGuiButton_render(EGuiButtonInstance_p widget, EGuiManager_p manager)
{

}

EGuiButtonInstance_p EGuiButton_create(void)
{
	EGuiButtonInstance_p widget = EMem.alloc(sizeof(EGuiButtonInstance));

	widget->render = (void*)EGuiButton_render;

	return widget;
}

_EGuiButton EGuiButton = {
	create: EGuiButton_create,
};