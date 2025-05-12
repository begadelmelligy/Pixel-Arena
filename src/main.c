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
#include "../systems/state_change.h"
#include "../systems/targeting.h"

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
    ecs_register_system(sStateChange);
    ecs_register_system(sTargeting);
    ecs_register_system(sPathFollowing);
    ecs_register_system(sMovement);
    ecs_register_system(sDamage);
    ecs_register_system(sRender);

    int enemyHero = create_entity(world);
    if (enemyHero != INVALID_ENTITY_ID) {
        world->entities[enemyHero].tag_mask |= TAG_ENEMY_HERO;

        cPosition p = {.x = 100.f, .y = 0.f};
        cVelocity v = {.dx = 0.f, .dy = 0.f, .speed = 200.0f};
        cHealth h = {.max_health = 100, .current_health = 100};
        cGridPosition g = {.x = p.x / CELL_SIZE, .y = p.y / CELL_SIZE};
        cPath path = {.length = 0, .current_index = 0, .active = false};
        cTarget target = {.current_target = 0, .target_distance = 100000};
        cAIState state = {.current_state = CHASING, .next_state = EMPTY};

        add_component(world, enemyHero, COMPONENT_POSITION, &p);
        add_component(world, enemyHero, COMPONENT_VELOCITY, &v);
        add_component(world, enemyHero, COMPONENT_HEALTH, &h);
        add_component(world, enemyHero, COMPONENT_GRIDPOSITION, &g);
        add_component(world, enemyHero, COMPONENT_PATH, &path);
        add_component(world, enemyHero, COMPONENT_TARGET, &target);
        add_component(world, enemyHero, COMPONENT_AISTATE, &state);
    }

    int creep1 = create_entity(world);
    if (creep1 != INVALID_ENTITY_ID) {
        world->entities[creep1].tag_mask |= TAG_PLAYER_CREEPS;

        cPosition p = {.x = 500.f, .y = 800.f};
        cGridPosition g = {.x = p.x / CELL_SIZE, .y = p.y / CELL_SIZE};

        add_component(world, creep1, COMPONENT_POSITION, &p);
        add_component(world, creep1, COMPONENT_GRIDPOSITION, &g);
    }

    int creep2 = create_entity(world);
    if (creep2 != INVALID_ENTITY_ID) {
        world->entities[creep2].tag_mask |= TAG_PLAYER_CREEPS;

        cPosition p = {.x = 200.f, .y = 600.f};
        cGridPosition g = {.x = p.x / CELL_SIZE, .y = p.y / CELL_SIZE};

        add_component(world, creep2, COMPONENT_POSITION, &p);
        add_component(world, creep2, COMPONENT_GRIDPOSITION, &g);
    }

    game_start(world);

    int counter = 0;
    while (!WindowShouldClose()) {
        float delta = GetFrameTime();
        if (delta >= 0.1) {
            delta = 0.1;
        }

        ecs_update(world, delta);

        if (counter >= 400) {
            if (world->entities[creep2].id != INVALID_ENTITY_ID) {
                destroy_entity(world, creep2);
            }
            counter = 0;
        }
        counter++;
    }

    destroy_world(world);
    CloseWindow();
    return 0;
}
