#include "raylib.h"
#include "../../components/position.h"

void sRender(void) {
    BeginDrawing();
    ClearBackground(BLACK);
    for (int i = 0; i < entity_count; i++) {
        if (entities[i].id == INVALID_ENTITY_ID) continue;
        int pos_idx = entities[i].component_indices[COMPONENT_POSITION];
        if (pos_idx != INVALID_COMPONENT_INDEX) {
            cPosition* pos = &((cPosition*)component_pools[COMPONENT_POSITION].data)[pos_idx];


            DrawCircle((int)pos->x, (int)pos->y, 50, RED);
        }
    }
    EndDrawing();
}
