#include <gui/EGuiButton.h>
#include <render/ERenderOpenGL.h>

void EGuiButton_render(EGuiButtonInstance_p widget, EGuiManager_p manager)
{

}

EGuiButtonInstance_p EGuiButton_create(void)
{
	EGuiButtonInstance_p widget = EMem.alloc(sizeof(EGuiButtonInstance));

	return widget;
}

_EGuiButton EGuiButton = {
	create: EGuiButton_create,
};