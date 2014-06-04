#include <gui/EGuiTextField.h>

EGuiTextFieldInstance_p EGuiTextField_create(void)
{
	EGuiTextFieldInstance_p widget = EMem.alloc(sizeof(EGuiTextFieldInstance));
	widget->value = EMem.alloc(sizeof(wchar_t)*256);
	widget->cursor = 0;
	widget->_text_widget = EGuiText.create();

	return widget;
}

_EGuiTextField EGuiTextField = {
	create: EGuiTextField_create,
};
