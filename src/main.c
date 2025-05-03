#include <stdio.h>

#include "globals.h"
#include "ecs.h"
#include "entity.h"
#include "world.h"


#include "../systems/damage.h"
#include "../systems/movement.h"
#include "../systems/input.h"
#include "../systems/render.h"



void game_start(World *world) {
    world->game_state.game_state = TITLE_SCREEN;
    world->game_state.is_paused = false;
}


int main(void) {
    InitWindow(WIDTH, HEIGHT, TITLE);
    SetTargetFPS(FPS);

    World *world = create_world();
    init_ecs();

    /*Register the systems here*/
    ecs_register_system(sInput);
    ecs_register_system(sMovement);
    ecs_register_system(sDamage);
    ecs_register_system(sRender);


    int enemyHero = create_entity(world);
    if (enemyHero != INVALID_ENTITY_ID) {
        cPosition p = {WIDTH/2, HEIGHT/2};
        cHealth h = {100, 100};
        cGridPosition g = {100, 100};
        add_component(world, enemyHero, COMPONENT_POSITION, &p);
        add_component(world, enemyHero, COMPONENT_HEALTH, &h);
        add_component(world, enemyHero, COMPONENT_GRIDPOSITION, &g);
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
