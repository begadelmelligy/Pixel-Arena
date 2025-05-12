#include "../../systems/state_change.h"

void sStateChange(World *world, float dt)
{
    (void)dt;
    ComponentMask required_comp = (1 << COMPONENT_AISTATE);

    if (!world->game_state.is_paused) {
        for (int i = 0; i < MAX_ENTITIES; i++) {

            if (world->entities[i].id == INVALID_ENTITY_ID)
                continue;
            if ((world->entities[i].component_masks & required_comp) == 0)
                continue;

            int state_idx = world->entities[i].component_indices[COMPONENT_AISTATE];
            cAIState *state = &((cAIState *)world->component_pools[COMPONENT_AISTATE].data)[state_idx];

            if (state->next_state == -1) {
                continue;
            }

            state->current_state = state->next_state;
            state->next_state = -1;
        }
    }
}
