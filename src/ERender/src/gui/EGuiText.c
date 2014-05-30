#include <gui/EGuiText.h>
#include <libfont.h>

void EGuiText_render(EGuiTextInstance_p widget, EGuiManager_p manager)
{

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, widget->tex);
	glUniform1i(glGetUniformLocation(manager->shaderManager->shader_id, "iTex0") , 0);

}

void EGuiText_setText(EGuiTextInstance_p widget, const wchar_t* text)
{
	widget->text = text;

	void* buffer = EMem.alloc(sizeof(char)*widget->width*widget->height);

	Libfont.setFont("../data/arial.my", widget->fontSize);
	Libfont.genText(buffer, text, widget->width, widget->height);

	glBindTexture(GL_TEXTURE_2D, widget->tex);

	glTexImage2D(
		GL_TEXTURE_2D,
		0,
		GL_R8,
		widget->width,
		widget->height,
		0,
		GL_RED,
		GL_UNSIGNED_BYTE,
		buffer
	);

	EMem.free(buffer);
}

EGuiTextInstance_p EGuiText_create(void)
{
	EGuiTextInstance_p widget = EMem.alloc(sizeof(EGuiTextInstance));
	widget->render = (void*)EGuiText_render;
	widget->fontSize = 14;
	
	glGenTextures(1, &widget->tex);
	glBindTexture(GL_TEXTURE_2D, widget->tex);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	return widget;
}

_EGuiText EGuiText = {
	create: EGuiText_create,
	setText: EGuiText_setText,
};