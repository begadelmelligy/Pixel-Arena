#include <stdio.h>

#include "ecs.h"
#include "entity.h"
#include "globals.h"
#include "grid.h"
#include "world.h"

#include "../systems/damage.h"
#include "../systems/input.h"
#include "../systems/movement.h"
#include "../systems/path_following.h"
#include "../systems/render.h"

void game_start(World *world)
{
    world->game_state.game_state = TITLE_SCREEN;
    world->game_state.is_paused = true;
}

int main(void)
{
    InitWindow(WIDTH, HEIGHT, TITLE);
    SetTargetFPS(FPS);

    World *world = create_world();
    init_ecs();

    /*Register the systems here*/
    ecs_register_system(sInput);
    ecs_register_system(sPathFollowing);
    ecs_register_system(sPathRequest);
    ecs_register_system(sMovement);
    ecs_register_system(sDamage);
    ecs_register_system(sRender);

    int enemyHero = create_entity(world);
    if (enemyHero != INVALID_ENTITY_ID) {
        cPosition p = {.x = 0, .y = 0};
        cVelocity v = {.dx = 0, .dy = 0};
        cHealth h = {.max_health = 100, .current_health = 100};
        cGridPosition g = {.x = p.x / CELL_SIZE, .y = p.y / CELL_SIZE};
        cPath path = {.length = 0, .current_index = 0, .active = false};

        add_component(world, enemyHero, COMPONENT_POSITION, &p);
        add_component(world, enemyHero, COMPONENT_VELOCITY, &v);
        add_component(world, enemyHero, COMPONENT_HEALTH, &h);
        add_component(world, enemyHero, COMPONENT_GRIDPOSITION, &g);
        add_component(world, enemyHero, COMPONENT_PATH, &path);
    }

    game_start(world);
    float delta;

    while (!WindowShouldClose()) {
        delta = GetFrameTime();
        ecs_update(world, delta);
    }

    destroy_world(world);
    CloseWindow();
    return 0;
}
