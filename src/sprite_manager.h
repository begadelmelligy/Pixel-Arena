#ifndef SPRITE_MANAGER_H
#define SPRITE_MANAGER_H

#include "../components/sprite.h"
#include "raylib.h"

enum SpriteSheetType {
    SHEET_GLADIATORS = 0,
    SHEET_MONSTERS = 1,
};

typedef struct SpriteManager {
    Texture2D glad_texture;
    Texture2D monster_texture;
    int sprite_height;
    int sprite_width;
} SpriteManager;

void init_sprite_manager(SpriteManager *manager);
void unload_sprite_manager(SpriteManager *manager);
SpriteSheetData get_sprite_sheet(SpriteManager *manager, enum SpriteSheetType sprite_sheet_type);

#endif
