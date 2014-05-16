#include "EGuiText.h"

GLuint texture = NULL;

void EGuiText_render(EGuiTextInstance_p widget, EGuiManager_p manager)
{

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);
	glUniform1i(glGetUniformLocation(manager->shaderManager->shader_id, "iTex0") , 0);

}

EGuiTextInstance_p EGuiText_create(char* text)
{
	EGuiTextInstance_p widget = EMem.alloc(sizeof(EGuiTextInstance));
	widget->render = (void*)EGuiText_render;
	widget->text = text;

/*
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	FT_Face face;
	FT_Library ft;

	FT_Init_FreeType(&ft);
	FT_New_Face(ft, "../data/arial.ttf", 0, &face);

	FT_GlyphSlot g = face->glyph;

	FT_Set_Pixel_Sizes(face, 0, 8);

	FT_Load_Char(face, 'H', FT_LOAD_RENDER);

	glTexImage2D(
		GL_TEXTURE_2D,
		0,
		GL_R8,
		g->bitmap.width,
		g->bitmap.rows,
		0,
		GL_RED,
		GL_UNSIGNED_BYTE,
		g->bitmap.buffer
	);

	FT_Done_Face(face);
	FT_Done_FreeType(ft);
*/
	return widget;
}

_EGuiText EGuiText = {
	create: EGuiText_create,
};