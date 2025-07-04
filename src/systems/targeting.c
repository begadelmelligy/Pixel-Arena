#include "../../systems/targeting.h"

int distance(int x, int y, int x_target, int y_target) { return abs(x - x_target) + abs(y - y_target); }

void sTargeting(World *world, float dt)
{
    (void)dt;

    ComponentMask required_comp =
        (1 << COMPONENT_GRIDPOSITION) | (1 << COMPONENT_TARGET) | (1 << COMPONENT_PATH) | (1 << COMPONENT_AISTATE);

    ComponentMask required_comp_target = (1 << COMPONENT_GRIDPOSITION);

    ComponentMask required_tag = TAG_ENEMY_HERO;
    ComponentMask required_tag_target = TAG_PLAYER_CREEPS;

    if (!world->game_state.is_paused)
        for (int i = 0; i < MAX_ENTITIES; i++) {
            if (world->entities[i].id == INVALID_ENTITY_ID)
                continue;
            if ((world->entities[i].tag_mask & required_tag) == 0)
                continue;
            if ((world->entities[i].component_masks & required_comp) == 0)
                continue;

            int grid_pos_idx = world->entities[i].component_indices[COMPONENT_GRIDPOSITION];
            int target_idx = world->entities[i].component_indices[COMPONENT_TARGET];

            cGridPosition *grid_pos_targetee =
                &((cGridPosition *)world->component_pools[COMPONENT_GRIDPOSITION].data)[grid_pos_idx];
            cTarget *target = &((cTarget *)world->component_pools[COMPONENT_TARGET].data)[target_idx];

            if (world->entities[target->current_target].id == INVALID_ENTITY_ID) {
                target->current_target = INVALID_ENTITY_ID;
                target->target_distance = 10000;
                target->is_active = false;
            }

            for (int j = 0; j < MAX_ENTITIES; j++) {
                if (world->entities[j].id == INVALID_ENTITY_ID)
                    continue;
                if ((world->entities[j].tag_mask & required_tag_target) == 0)
                    continue;
                if ((world->entities[j].component_masks & required_comp_target) == 0)
                    continue;

                int grid_pos_idx = world->entities[j].component_indices[COMPONENT_GRIDPOSITION];
                cGridPosition *grid_pos_target =
                    &((cGridPosition *)world->component_pools[COMPONENT_GRIDPOSITION].data)[grid_pos_idx];

                float temp_target_distance =
                    distance(grid_pos_targetee->x, grid_pos_targetee->y, grid_pos_target->x, grid_pos_target->y);

                if (target->target_distance > temp_target_distance) {
                    if (target->current_target == world->entities[j].id) {
                        target->is_new = true;

                    } else {
                        target->is_new = false;
                    }

                    target->target_distance = temp_target_distance;
                    target->current_target = world->entities[j].id;
                    target->is_active = true;
                }
            }
        }
}
