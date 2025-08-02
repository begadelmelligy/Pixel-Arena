#include "fonts.h"

Fonts fonts = {0};

void init_fonts(void)
{

    Font main_font = LoadFont("assets/fonts/JetBrainsMonoNerdFont-Bold.ttf");
    Font text_font = LoadFont("assets/fonts/ARLRDBD.ttf");

    fonts.main = main_font;
    fonts.text = text_font;
}
