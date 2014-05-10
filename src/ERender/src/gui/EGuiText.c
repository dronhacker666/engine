#include "EGuiText.h"

void EGuiText_render(EGuiTextInstance_p widget)
{
	printf("%s\n", widget->text);
}

EGuiTextInstance_p EGuiText_create(char* text)
{
	EGuiTextInstance_p widget = EMem.alloc(sizeof(EGuiTextInstance));

	widget->render = (void*)EGuiText_render;
	widget->text = text;
	return widget;
}

_EGuiText EGuiText = {
	create: EGuiText_create,
};