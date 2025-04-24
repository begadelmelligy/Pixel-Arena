#include "raylib.h"
#include "ecs.h"
#include "systems.h"
#include "game.h"
#include <stdio.h>

#define HEIGHT 1200.0
#define WIDTH 1600.0
#define FPS 60
#define TITLE "PIXEL ARENA"


int main(void) {
    InitWindow(WIDTH, HEIGHT, TITLE);
    SetTargetFPS(FPS);

    GameState gameState;
    gameState.mode = 1;

    init_ecs();


    int enemyHero = create_entity();
    if (enemyHero != INVALID_ENTITY_ID) {
        Position p = {WIDTH/2, HEIGHT/2};
        Health h = {100, 100};
        add_component(enemyHero, COMPONENT_POSITION, &p);
        add_component(enemyHero, COMPONENT_HEALTH, &h);
    }

    /*int e2 = create_entity();*/
    /*if (e2 != INVALID_ENTITY_ID) {*/
    /*    Position p = {200, 200};*/
    /*    Velocity v = {-30, 20};*/
    /*    add_component(e2, COMPONENT_POSITION, &p);*/
    /*    add_component(e2, COMPONENT_VELOCITY, &v);*/
    /*}*/

    int counter = 0;

    while (!WindowShouldClose()) {
        if (gameState.mode != 0){
            float delta = GetFrameTime();
            if (counter >= 200){
                applyDamage(enemyHero, 10);
                counter = 0;
            }
            counter++;
            sMovement(delta);
            sDamage();
            sRender();
        }
        else {
            /*Enter main menu logic here*/
        }
    }

    CloseWindow();
    return 0;
}
