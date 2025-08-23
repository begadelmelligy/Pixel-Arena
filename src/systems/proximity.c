#include "../../systems/proximity.h"
#include "../dev_tools/profiler.h"
#include "stdbool.h"
#include <stdio.h>

#define TOLERANCE 2

void sProximity(World *world, float dt)
{
    PROFILE_BEGIN("System Proximity");
    (void)dt;
    ComponentMask required_comp = (1 << COMPONENT_AISTATE) | (1 << COMPONENT_TARGET) | (1 << COMPONENT_PATH) | (1 << COMPONENT_HOVER_RANGE);

    if (!world->game_state.is_paused) {
        for (int i = 0; i < MAX_ENTITIES; i++) {

            if (world->entities[i].id == INVALID_ENTITY_ID)
                continue;
            if ((world->entities[i].component_masks & required_comp) != required_comp)
                continue;

            int aistate_idx = world->entities[i].component_indices[COMPONENT_AISTATE];
            int target_idx = world->entities[i].component_indices[COMPONENT_TARGET];
            int path_idx = world->entities[i].component_indices[COMPONENT_PATH];
            int hover_range_idx = world->entities[i].component_indices[COMPONENT_HOVER_RANGE];

            cAIState *aistate = &((cAIState *)world->component_pools[COMPONENT_AISTATE].data)[aistate_idx];
            cTarget *target = &((cTarget *)world->component_pools[COMPONENT_TARGET].data)[target_idx];
            cPath *path = &((cPath *)world->component_pools[COMPONENT_PATH].data)[path_idx];
            cHoverRange *hover_range = &((cHoverRange *)world->component_pools[COMPONENT_HOVER_RANGE].data)[hover_range_idx];

            /*If target is gone (-1) stop pathing request*/
            if (target->current_target == INVALID_ENTITY_ID) {
                path->length = 0;
                path->current_index = 0;
                path->active = false;
                path->request.pending = false;
                continue;
            }

            int target_grid_pos_idx = world->entities[target->current_target].component_indices[COMPONENT_GRIDPOSITION];
            cGridPosition *target_grid_pos = &((cGridPosition *)world->component_pools[COMPONENT_GRIDPOSITION].data)[target_grid_pos_idx];

            if (target->is_active) {
                if (target->target_distance > hover_range->max_range) {
                    enum AIState to_state = STATE_CHASING;
                    bool can_transition = transition(aistate, to_state);

                    if (can_transition) {
                        if (abs(target_grid_pos->x - path->request.target_x) > TOLERANCE ||
                            abs(target_grid_pos->y - path->request.target_y) > TOLERANCE) {
                            path->request.pending = true;
                            path->request.target_x = target_grid_pos->x;
                            path->request.target_y = target_grid_pos->y;
                            continue;
                        }
                    }
                }

                if (target->target_distance <= hover_range->max_range) {
                    enum AIState to_state = STATE_IDLE;
                    bool can_transition = transition(aistate, to_state);

                    if (can_transition) {
                        path->length = 0;
                        path->current_index = 0;
                        path->active = false;
                        path->request.pending = false;
                        continue;
                    }
                }
            }
        }
    }
    PROFILE_END("System Proximity");
}
