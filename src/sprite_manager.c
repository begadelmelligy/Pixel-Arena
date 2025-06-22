#include "sprite_manager.h"
#include "raylib.h"

void init_sprite_manager(SpriteManager *manager)
{
    /*load the different textures here*/
    manager->glad_texture = LoadTexture("assets/32rogues/rogues.png");
    SetTextureFilter(manager->glad_texture, TEXTURE_FILTER_POINT);
    manager->glad_sprite_height = 32;
    manager->glad_sprite_width = 32;
}

void unload_sprite_manager(SpriteManager *manager)
{
    /*unload the different textures here*/
    UnloadTexture(manager->glad_texture);
}
