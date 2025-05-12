#include "../../systems/proximity.h"
#include "stdbool.h"
#include <stdio.h>

void sProximity(World *world, float dt)
{
    (void)dt;
    ComponentMask required_comp = (1 << COMPONENT_AISTATE) | (1 << COMPONENT_TARGET) | (1 << COMPONENT_PATH);

    if (!world->game_state.is_paused) {
        for (int i = 0; i < world->entity_count; i++) {

            if (world->entities[i].id == INVALID_ENTITY_ID)
                continue;
            if ((world->entities[i].component_masks & required_comp) == 0)
                continue;

            int state_idx = world->entities[i].component_indices[COMPONENT_AISTATE];
            int target_idx = world->entities[i].component_indices[COMPONENT_TARGET];
            int path_idx = world->entities[i].component_indices[COMPONENT_PATH];

            cAIState *state = &((cAIState *)world->component_pools[COMPONENT_AISTATE].data)[state_idx];
            cTarget *target = &((cTarget *)world->component_pools[COMPONENT_TARGET].data)[target_idx];
            cPath *path = &((cPath *)world->component_pools[COMPONENT_PATH].data)[path_idx];

            int target_grid_pos_idx = world->entities[target->current_target].component_indices[COMPONENT_GRIDPOSITION];
            cGridPosition *target_grid_pos =
                &((cGridPosition *)world->component_pools[COMPONENT_GRIDPOSITION].data)[target_grid_pos_idx];

            if (target->active) {

                if (target->target_distance > 10) {
                    bool can_transition = transition(state, STATE_CHASING);

                    if (can_transition) {

                        path->request.request_pending = true;
                        path->request.target_x = target_grid_pos->x;
                        path->request.target_y = target_grid_pos->y;
                        continue;
                    }
                }

                if (target->target_distance <= 10) {
                    bool can_transition = transition(state, STATE_COMBAT);

                    if (can_transition) {
                        for (int i = 0; i < path->length; i++) {
                            path->nodes[i] = NULL;
                        }
                        path->length = 0;
                        path->current_index = 0;
                        path->active = 0;
                        path->request.request_pending = false;
                        printf("current state: %d\n", state->current_state);
                        continue;
                    }
                }
            }
        }
    }
}
