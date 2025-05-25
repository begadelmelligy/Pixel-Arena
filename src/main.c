#include <stdio.h>

#include "ds.h"

#include "ecs.h"
#include "entity.h"
#include "globals.h"
#include "grid.h"
#include "world.h"

#include "../systems/ability_casting.h"
#include "../systems/damage.h"
#include "../systems/input.h"
#include "../systems/movement.h"
#include "../systems/path_following.h"
#include "../systems/proximity.h"
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
    ecs_register_system(sProximity);
    ecs_register_system(sPathRequest);
    ecs_register_system(sPathFollowing);
    ecs_register_system(sMovement);
    ecs_register_system(sAbilityCasting);
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
        cTarget target = {.current_target = 0, .target_distance = 100000, .is_new = true, .is_active = false};
        cAIState state = {.current_state = STATE_IDLE, .next_state = STATE_EMPTY};
        cAbilityCaster ability_caster;

        ability_caster.ability_count = 1;

        float cd = 0.0f;
        dictInit(&ability_caster.remaining_cd, 1, sizeof(float));
        dictAdd(&ability_caster.remaining_cd, ABILITY_CHAIN_LIGHTNING, &cd);

        Ability ability1 = all_abilities[ABILITY_CHAIN_LIGHTNING];
        dictInit(&ability_caster.abilities, 1, sizeof(Ability));
        dictAdd(&ability_caster.abilities, ABILITY_CHAIN_LIGHTNING, &ability1);

        cCastRequest cast_request = {.ability_id = ABILITY_CHAIN_LIGHTNING, .target = 1, .is_active = true};

        add_component(world, enemyHero, COMPONENT_POSITION, &p);
        add_component(world, enemyHero, COMPONENT_VELOCITY, &v);
        add_component(world, enemyHero, COMPONENT_HEALTH, &h);
        add_component(world, enemyHero, COMPONENT_GRIDPOSITION, &g);
        add_component(world, enemyHero, COMPONENT_PATH, &path);
        add_component(world, enemyHero, COMPONENT_TARGET, &target);
        add_component(world, enemyHero, COMPONENT_AISTATE, &state);
        add_component(world, enemyHero, COMPONENT_ABILITY_CASTER, &ability_caster);
        add_component(world, enemyHero, COMPONENT_CAST_REQUEST, &cast_request);
    }

    int test = create_entity(world);
    if (test != INVALID_ENTITY_ID) {
        world->entities[test].tag_mask |= TAG_PLAYER_CREEPS;

        cPosition p = {.x = 300.f, .y = 300.f};
        cVelocity v = {.dx = 0.f, .dy = 0.f, .speed = 200.0f};
        cHealth h = {.max_health = 100, .current_health = 100};
        cGridPosition g = {.x = p.x / CELL_SIZE, .y = p.y / CELL_SIZE};

        add_component(world, test, COMPONENT_POSITION, &p);
        add_component(world, test, COMPONENT_VELOCITY, &v);
        add_component(world, test, COMPONENT_HEALTH, &h);
        add_component(world, test, COMPONENT_GRIDPOSITION, &g);
    }

    game_start(world);

    while (!WindowShouldClose()) {
        float delta = GetFrameTime();
        if (delta >= 0.1) {
            delta = 0.1;
        }

        ecs_update(world, delta);
    }

    destroy_world(world);
    CloseWindow();
    return 0;
}
