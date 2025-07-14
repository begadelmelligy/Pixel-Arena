#include "ecs.h"
#include "game/data/entity_data.h"
#include "globals.h"
#include "raylib.h"
#include "sprite_manager.h"
#include "world.h"
#include <stdlib.h>
#include <string.h>

#include "../systems/ability_casting.h"
#include "../systems/damage.h"
#include "../systems/input.h"
#include "../systems/movement.h"
#include "../systems/path_following.h"
#include "../systems/proximity.h"
#include "../systems/render.h"
#include "../systems/state_change.h"
#include "../systems/targeting.h"

#include "../styles/dark/style_dark.h"

void game_start(World *world)
{
    world->game_state.game_state = TITLE_SCREEN;
    world->game_state.is_paused = true;
}

int main(void)
{
    InitWindow(WIDTH, HEIGHT, TITLE);
    SetTargetFPS(FPS);

    Font custom_font = LoadFont("assets/fonts/JetBrainsMonoNerdFont-Bold.ttf");
    /*GuiLoadStyleDark();*/
    GuiSetStyle(DEFAULT, TEXT_SIZE, 16);
    GuiSetFont(custom_font);

    World *world = create_world();
    init_ecs();

    SpriteManager *sm = malloc(sizeof(SpriteManager));
    world->sprite_manager = sm;
    init_sprite_manager(world->sprite_manager);

    /*Register the systems here*/
    ecs_register_system(sInput);
    ecs_register_system(sStateChange);
    ecs_register_system(sTargeting);
    ecs_register_system(sProximity);
    ecs_register_system(sPathRequest);
    ecs_register_system(sPathFollowing);
    ecs_register_system(sMovement);
    ecs_register_system(sAbilityCasting);
    ecs_register_system(sDamage);
    ecs_register_system(sRender);

    /*summon entities*/
    summon_enemy_caster(world, sm, 100.f, 0.f);
    summon_test_entity(world, sm, 400.f, 200.f);

    game_start(world);

    while (!WindowShouldClose()) {
        float delta = GetFrameTime();

        /*clips delta change for debugging*/
        if (delta >= 0.1) {
            delta = 0.1;
        }

        ecs_update(world, delta);
    }

    destroy_world(world);
    free(sm);
    CloseWindow();
    return 0;
}
