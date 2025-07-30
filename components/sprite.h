#ifndef SPRITE_H
#define SPRITE_H

#include "raylib.h"

typedef struct SpriteSheetData {
    Texture2D sprite_sheet;
    int sprite_height;
    int sprite_width;
} SpriteSheetData;

typedef struct cSprite {
    SpriteSheetData sprite_sheet_data;
    int sprite_row;
    int sprite_col;
    int direction;
} cSprite;

#endif
