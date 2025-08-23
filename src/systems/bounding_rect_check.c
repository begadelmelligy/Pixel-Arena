#include "../../systems/bounding_rect_check.h"
#include "../dev_tools/profiler.h"
#include "stdio.h"

void sBoundingRectCheck(World *world, float dt)
{
    (void)dt;
    PROFILE_BEGIN("System BoundingRectCheck");
    ComponentMask required_comp = (1 << COMPONENT_BOUNDING_RECT);

    if (!world->game_state.is_paused && world->game_state.game_state == GAME_COMBAT) {
        for (int i = 0; i < MAX_ENTITIES; i++) {

            if (world->entities[i].id == INVALID_ENTITY_ID)
                continue;
            if ((world->entities[i].component_masks & required_comp) != required_comp)
                continue;

            int bounding_rect_idx = world->entities[i].component_indices[COMPONENT_BOUNDING_RECT];
            cBoundingRect *bounding_rect = &((cBoundingRect *)world->component_pools[COMPONENT_BOUNDING_RECT].data)[bounding_rect_idx];
            for (int j = 0; j < MAX_ENTITIES; j++) {
                if (i == j)
                    continue;

                if (world->entities[j].id == INVALID_ENTITY_ID)
                    continue;
                if ((world->entities[j].component_masks & required_comp) != required_comp)
                    continue;

                int bounding_rect_idx_j = world->entities[j].component_indices[COMPONENT_BOUNDING_RECT];
                cBoundingRect *bounding_rect_j =
                    &((cBoundingRect *)world->component_pools[COMPONENT_BOUNDING_RECT].data)[bounding_rect_idx_j];

                // This will be used to do whatever is needed on collision
                /*if (CheckCollisionRecs(bounding_rect->rect, bounding_rect_j->rect)) {*/
                /*    printf("Entity: %d, collided with %d \n", world->entities[i].id, world->entities[j].id);*/
                /*}*/
            }
        }
    }
    PROFILE_END("System BoundingRectCheck");
}
