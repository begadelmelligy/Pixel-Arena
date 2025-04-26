#include "raylib.h"
#include "../../systems/render.h"
#include "../../components/position.h"

void sRender(World *world, float dt) {
    (void)dt;
    BeginDrawing();
    ClearBackground(BLACK);
    for (int i = 0; i < world->entity_count; i++) {
        if (world->entities[i].id == INVALID_ENTITY_ID) continue;
        int pos_idx = world->entities[i].component_indices[COMPONENT_POSITION];
        if (pos_idx != INVALID_COMPONENT_INDEX) {
            cPosition* pos = &((cPosition*)world->component_pools[COMPONENT_POSITION].data)[pos_idx];


            DrawCircle((int)pos->x, (int)pos->y, 50, RED);
        }
    }
    EndDrawing();
}
