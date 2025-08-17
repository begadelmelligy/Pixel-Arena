#include "../../systems/movement.h"
#include "../dev_tools/profiler.h"

void sMovement(World *world, float delta)
{

    PROFILE_BEGIN("System Movement");
    ComponentMask required_comp = (1 << COMPONENT_POSITION) | (1 << COMPONENT_VELOCITY) | (1 << COMPONENT_GRIDPOSITION);

    if (!world->game_state.is_paused) {
        for (int i = 0; i < MAX_ENTITIES; i++) {

            if (world->entities[i].id == INVALID_ENTITY_ID)
                continue;
            if ((world->entities[i].component_masks & required_comp) != required_comp)
                continue;

            int pos_idx = world->entities[i].component_indices[COMPONENT_POSITION];
            int grid_pos_idx = world->entities[i].component_indices[COMPONENT_GRIDPOSITION];
            int vel_idx = world->entities[i].component_indices[COMPONENT_VELOCITY];

            cPosition *pos = &((cPosition *)world->component_pools[COMPONENT_POSITION].data)[pos_idx];
            cGridPosition *grid_pos = &((cGridPosition *)world->component_pools[COMPONENT_GRIDPOSITION].data)[grid_pos_idx];
            cVelocity *vel = &((cVelocity *)world->component_pools[COMPONENT_VELOCITY].data)[vel_idx];

            pos->x += vel->dx * delta;
            pos->y += vel->dy * delta;
            grid_pos->x = pos->x / CELL_SIZE;
            grid_pos->y = pos->y / CELL_SIZE;

            // If entity has bounding box. Update it's position
            if ((world->entities[i].component_masks & (1 << COMPONENT_BOUNDING_RECT)) == (1 << COMPONENT_BOUNDING_RECT)) {
                int bounding_box_idx = world->entities[i].component_indices[COMPONENT_BOUNDING_RECT];
                cBoundingRect *bounding_box = &((cBoundingRect *)world->component_pools[COMPONENT_BOUNDING_RECT].data)[bounding_box_idx];

                bounding_box->rect.x += vel->dx * delta;
                bounding_box->rect.y += vel->dy * delta;
            }
        }
    }
    PROFILE_END("System Movement");
}
