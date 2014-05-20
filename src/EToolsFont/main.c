#include "libfont.h"
#include "ELib.h"

int main(void)
{
	Libfont.init();
	Libfont.setFont("../data/arial.my", 14);

	char* buffer = EMem.alloc(sizeof(char)*100*20);

	Libfont.genText(buffer, "fps", 100, 20);

	return 0;
}