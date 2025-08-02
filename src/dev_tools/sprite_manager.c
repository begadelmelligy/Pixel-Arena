#include "sprite_manager.h"
#include "raylib.h"

void init_sprite_manager(SpriteManager *manager)
{
    /*load the different textures here*/
    manager->glad_texture = LoadTexture("assets/32rogues/rogues.png");
    SetTextureFilter(manager->glad_texture, TEXTURE_FILTER_POINT);

    manager->monster_texture = LoadTexture("assets/32rogues/monsters.png");
    SetTextureFilter(manager->monster_texture, TEXTURE_FILTER_POINT);

    manager->sprite_height = 32;
    manager->sprite_width = 32;
}

SpriteSheetData get_sprite_sheet(SpriteManager *manager, enum SpriteSheetType sprite_sheet_type)
{
    SpriteSheetData data = {0};
    switch (sprite_sheet_type) {
        case SHEET_GLADIATORS:
            data.sprite_sheet = manager->glad_texture;
            data.sprite_width = manager->sprite_width;
            data.sprite_height = manager->sprite_height;
            break;
        case SHEET_MONSTERS:
            data.sprite_sheet = manager->monster_texture;
            data.sprite_width = manager->sprite_width;
            data.sprite_height = manager->sprite_height;
            break;
    };

    return data;
}

void unload_sprite_manager(SpriteManager *manager)
{
    /*unload the different textures here*/
    UnloadTexture(manager->glad_texture);
}
