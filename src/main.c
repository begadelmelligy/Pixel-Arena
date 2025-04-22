#include "raylib.h"
#include "ecs.h"
#include "systems.h"
#include <stdio.h>


int main(void) {
    InitWindow(1600, 1200, "Pixel Arena");
    SetTargetFPS(60);

    init_ecs();

    int e1 = create_entity();
    if (e1 != INVALID_ENTITY_ID) {
        Position p = {100, 100};
        Velocity v = {50, 50};
        add_component(e1, COMPONENT_POSITION, &p);
        add_component(e1, COMPONENT_VELOCITY, &v);
    }

    int e2 = create_entity();
    if (e2 != INVALID_ENTITY_ID) {
        Position p = {200, 200};
        Velocity v = {-30, 20};
        add_component(e2, COMPONENT_POSITION, &p);
        add_component(e2, COMPONENT_VELOCITY, &v);
    }


    while (!WindowShouldClose()) {
        float delta = GetFrameTime();
        movement_system(delta);
        render_system();
    }

    CloseWindow();
    return 0;
}
