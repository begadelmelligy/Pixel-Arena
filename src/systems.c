#include "systems.h"
#include "ecs.h"
#include "raylib.h"


extern Entity entities[MAX_ENTITIES];
extern int entity_count;
extern ComponentPool component_pools[NUM_COMPONENT_TYPES];


void movement_system(float delta) {
    for (int i = 0; i < entity_count; i++) {
        if (entities[i].id == INVALID_ENTITY_ID) continue;
        int pos_idx = entities[i].component_indices[COMPONENT_POSITION];
        int vel_idx = entities[i].component_indices[COMPONENT_VELOCITY];
        if (pos_idx != INVALID_COMPONENT_INDEX && vel_idx != INVALID_COMPONENT_INDEX) {
            Position* pos = &((Position*)component_pools[COMPONENT_POSITION].data)[pos_idx];
            Velocity* vel = &((Velocity*)component_pools[COMPONENT_VELOCITY].data)[vel_idx];
            pos->x += vel->dx * delta;
            pos->y += vel->dy * delta;
        }
    }
}


void render_system() {
    BeginDrawing();
    ClearBackground(BLACK);
    for (int i = 0; i < entity_count; i++) {
        if (entities[i].id == INVALID_ENTITY_ID) continue;
        int pos_idx = entities[i].component_indices[COMPONENT_POSITION];
        if (pos_idx != INVALID_COMPONENT_INDEX) {
            Position* pos = &((Position*)component_pools[COMPONENT_POSITION].data)[pos_idx];
            DrawCircle((int)pos->x, (int)pos->y, 10, RED);
        }
    }
    EndDrawing();
}
