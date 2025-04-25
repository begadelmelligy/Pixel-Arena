#include "../../components/position.h"
#include "../../components/velocity.h"

#include 

void sMovement(float delta) {
    for (int i = 0; i < entity_count; i++) {
        if (entities[i].id == INVALID_ENTITY_ID) continue;
        int pos_idx = entities[i].component_indices[COMPONENT_POSITION];
        int vel_idx = entities[i].component_indices[COMPONENT_VELOCITY];
        if (pos_idx != INVALID_COMPONENT_INDEX && vel_idx != INVALID_COMPONENT_INDEX) {
            cPosition* pos = &((cPosition*)component_pools[COMPONENT_POSITION].data)[pos_idx];
            cVelocity* vel = &((cVelocity*)component_pools[COMPONENT_VELOCITY].data)[vel_idx];


            pos->x += vel->dx * delta;
            pos->y += vel->dy * delta;
        }
    }
}
