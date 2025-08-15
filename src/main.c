#include "ecs_core/ecs.h"
#include "game/data/entity_data.h"
#include "raygui.h"
#include "raylib.h"
#include "world.h"
#include <stdio.h>
#include <string.h>

#include "globals.h"
#include "support/fonts.h"

#include "dev_tools/profiler.h"

#include "../systems/ability_casting.h"
#include "../systems/ability_cooldown.h"
#include "../systems/ability_picker.h"
#include "../systems/damage.h"
#include "../systems/input.h"
#include "../systems/movement.h"
#include "../systems/path_following.h"
#include "../systems/proximity.h"
#include "../systems/render.h"
#include "../systems/state_change.h"
#include "../systems/summon.h"
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

    init_fonts();

    /*GuiLoadStyleDark();*/
    GuiSetStyle(DEFAULT, TEXT_SIZE, 16);
    GuiSetFont(fonts.main);

    World *world = create_world();
    init_ecs();

    /*Register the systems here*/
    ecs_register_system(sInput);
    ecs_register_system(sSummon);
    ecs_register_system(sTargeting);
    ecs_register_system(sProximity);
    ecs_register_system(sPathRequest);
    ecs_register_system(sPathFollowing);
    ecs_register_system(sMovement);
    ecs_register_system(sAbilityPicker);
    ecs_register_system(sAbilityCasting);
    ecs_register_system(sAbilityCooldown);
    ecs_register_system(sDamage);
    ecs_register_system(sStateChange);
    ecs_register_system(sRender);

    /*summon entities*/
    summon_enemy_caster(world, 100.f, 100.f);

    game_start(world);

    while (!WindowShouldClose()) {
        profiler_reset();
        float delta = GetFrameTime();

        /*clips delta change for debugging*/
        if (delta >= 0.1) {
            delta = 0.1;
        }

        PROFILE_BEGIN("Main Loop");
        ecs_update(world, delta);
        PROFILE_END("Main Loop");

        if (profiler_enable) {
            profiler_draw(WIDTH - 300, 10, fonts.text);
        }
    }

    destroy_world(world);
    CloseWindow();
    return 0;
}
