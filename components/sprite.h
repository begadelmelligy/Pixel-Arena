#ifndef SPRITE_H
#define SPRITE_H

#include "raylib.h"

typedef struct cSprite {
    Texture2D spritesheet;
    int sprite_height;
    int sprite_width;
    int sprite_row;
    int sprite_col;
} cSprite;

#endif
