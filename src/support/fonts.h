#ifndef FONTS_H
#define FONTS_H

#include "raylib.h"

typedef struct Fonts {
    Font main;
    Font text;
} Fonts;

extern Fonts fonts;

void init_fonts(void);

#endif
