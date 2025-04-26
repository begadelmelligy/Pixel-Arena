#include "globals.h"
#include "raylib.h"
#include <stdio.h>

#include "ecs.h"
#include "entity.h"
#include "world.h"

#include "../systems/damage.h"
#include "../systems/movement.h"
#include "../systems/render.h"

#define HEIGHT 1200.0
#define WIDTH 1600.0
#define FPS 60
#define TITLE "PIXEL ARENA"


int main(void) {
    InitWindow(WIDTH, HEIGHT, TITLE);
    SetTargetFPS(FPS);

    World *world = create_world();
    init_ecs();

    /*Register the systems here*/
    ecs_register_system(sMovement);
    ecs_register_system(sDamage);
    ecs_register_system(sRender);


    int enemyHero = create_entity(world);
    if (enemyHero != INVALID_ENTITY_ID) {
        cPosition p = {WIDTH/2, HEIGHT/2};
        cHealth h = {100, 100};
        cVelocity v = {40, 40};
        add_component(world, enemyHero, COMPONENT_POSITION, &p);
        add_component(world, enemyHero, COMPONENT_HEALTH, &h);
        add_component(world, enemyHero, COMPONENT_VELOCITY, &v);
    }


    while (!WindowShouldClose()) {
        float delta = GetFrameTime();
        ecs_update(world, delta);
    }

    destroy_world(world);
    CloseWindow();
    return 0;
}
