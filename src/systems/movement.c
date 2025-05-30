#include "../../systems/movement.h"

void sMovement(World *world, float delta)
{

    ComponentMask required_comp = (1 << COMPONENT_POSITION) | (1 << COMPONENT_VELOCITY) | (1 << COMPONENT_GRIDPOSITION);

    if (!world->game_state.is_paused) {
        for (int i = 0; i < MAX_ENTITIES; i++) {

            if (world->entities[i].id == INVALID_ENTITY_ID)
                continue;
            if ((world->entities[i].component_masks & required_comp) == 0)
                continue;

            int pos_idx = world->entities[i].component_indices[COMPONENT_POSITION];
            int grid_pos_idx = world->entities[i].component_indices[COMPONENT_GRIDPOSITION];
            int vel_idx = world->entities[i].component_indices[COMPONENT_VELOCITY];

            cPosition *pos = &((cPosition *)world->component_pools[COMPONENT_POSITION].data)[pos_idx];
            cGridPosition *grid_pos =
                &((cGridPosition *)world->component_pools[COMPONENT_GRIDPOSITION].data)[grid_pos_idx];
            cVelocity *vel = &((cVelocity *)world->component_pools[COMPONENT_VELOCITY].data)[vel_idx];

            pos->x += vel->dx * delta;
            pos->y += vel->dy * delta;
            grid_pos->x = pos->x / CELL_SIZE;
            grid_pos->y = pos->y / CELL_SIZE;
        }
    }
}
