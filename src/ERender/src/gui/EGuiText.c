#include <gui/EGuiText.h>
#include <libfont.h>

GLuint texture = -1;

void EGuiText_render(EGuiTextInstance_p widget, EGuiManager_p manager)
{

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);
	glUniform1i(glGetUniformLocation(manager->shaderManager->shader_id, "iTex0") , 0);

}

void EGuiText_setText(EGuiTextInstance_p widget, const char* text)
{
	widget->text = text;

	void* buffer = EMem.alloc(sizeof(char)*200*100);
	Libfont.genText(buffer, text, 200, 100);

	glBindTexture(GL_TEXTURE_2D, texture);

	glTexImage2D(
		GL_TEXTURE_2D,
		0,
		GL_R8,
		200,
		100,
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
	
	Libfont.init();

	if(! Libfont.setFont("../data/arial.my", 14) ){
		exit(0);
	}

	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	return widget;
}

_EGuiText EGuiText = {
	create: EGuiText_create,
	setText: EGuiText_setText,
};