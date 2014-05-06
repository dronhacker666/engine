#include "EGuiButton.h"

void EGuiButton_render(EGuiButtonInstance_p widget)
{

}

EGuiButtonInstance_p EGuiButton_create(void)
{
	new(widget, EGuiButtonInstance);

	widget->render = (void*)EGuiButton_render;

	return widget;
}

_EGuiButton EGuiButton = {
	create: EGuiButton_create,
};