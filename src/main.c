#include "raylib.h"
#include "ecs.h"
#include "systems.h"
#include <stdio.h>

int main(void) {
    InitWindow(1600, 1200, "Pixel Arena");
    SetTargetFPS(60);

    init_ecs();

    // Create some entities
    int e1 = create_entity();
    if (e1 != INVALID_ENTITY_ID) {
        add_position(e1, 100, 100);
        add_velocity(e1, 50, 50);
    }

    int e2 = create_entity();
    if (e2 != INVALID_ENTITY_ID) {
        add_position(e2, 200, 200);
        add_velocity(e2, -30, 20);
    }
    printf("Entity id: %d", e1);

    while (!WindowShouldClose()) {
        float delta = GetFrameTime();
        movement_system(delta);
        render_system();
    }


    CloseWindow();
    return 0;
}
