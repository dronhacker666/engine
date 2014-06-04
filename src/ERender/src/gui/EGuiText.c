#include <gui/EGuiText.h>
#include <render/ERenderOpenGL.h>
#include <libfont.h>
#include <stdint.h>

void EGuiText_render(EGuiTextInstance_p widget)
{
}

void EGuiText_setText(EGuiTextInstance_p widget, const wchar_t* text)
{
	widget->text = text;

	uint8_t* buffer = EMem.alloc(sizeof(uint8_t)*widget->width*widget->height);

	char* filename = "../data/arial.my";

	if(!Libfont.setFont(filename, widget->fontSize)){
		printf("Failed open file\"%s\"\n", filename);
		exit(1);
	}
	Libfont.genText(buffer, text, widget->width, widget->height);

	EMem.free(widget->buffer);
	widget->buffer = EMem.alloc(sizeof(uint8_t)*4*widget->width*widget->height);
	int i;
	int px_size = sizeof(uint8_t)*4;
	uint8_t* buff = widget->buffer;
	for(i=0; i<widget->width*widget->height; i++){
		buff[i*px_size+0] = buffer[i];
		buff[i*px_size+1] = buffer[i];
		buff[i*px_size+2] = buffer[i];
		buff[i*px_size+3] = buffer[i];
	}
	EMem.free(buffer);

	widget->hasChanged = true;
}

EGuiTextInstance_p EGuiText_create(void)
{
	EGuiTextInstance_p widget = EMem.alloc(sizeof(EGuiTextInstance));
	return widget;
}

_EGuiText EGuiText = {
	create: EGuiText_create,
	setText: EGuiText_setText,
};