#ifndef SPRITE_MANAGER_H
#define SPRITE_MANAGER_H

#include "raylib.h"

typedef struct SpriteManager {
    Texture2D glad_texture;
    int glad_sprite_height;
    int glad_sprite_width;
} SpriteManager;

void init_sprite_manager(SpriteManager *manager);
void unload_sprite_manager(SpriteManager *manager);
Rectangle sprite_sheet_indexer(int index, int frame_width, int frame_height, int cols);

#endif
