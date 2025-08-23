#include "../../systems/targeting.h"
#include "../dev_tools/profiler.h"

int distance(int x, int y, int x_target, int y_target) { return abs(x - x_target) + abs(y - y_target); }

enum EntityTag legal_entity_target[NUM_ENTITY_TAGS][NUM_ENTITY_TAGS - 1] = {
    [TAG_ENEMY_HERO] = {TAG_PLAYER_BOSS, TAG_PLAYER_HERO, TAG_PLAYER_CREEPS},
    [TAG_PLAYER_CREEPS] = {TAG_ENEMY_HERO},
    [TAG_PLAYER_BOSS] = {TAG_ENEMY_HERO},
    [TAG_PLAYER_HERO] = {TAG_ENEMY_HERO},
};

int legal_entity_count[NUM_ENTITY_TAGS] = {3, 1, 1, 1};

bool can_target(enum EntityTag targetee, enum EntityTag target)
{
    for (int i = 0; i < legal_entity_count[targetee]; i++) {
        if (legal_entity_target[targetee][i] == target) {
            return true;
        }
    }
    return false;
}

void sTargeting(World *world, float dt)
{
    PROFILE_BEGIN("System Targeting");
    (void)dt;

    ComponentMask required_comp = (1 << COMPONENT_GRIDPOSITION) | (1 << COMPONENT_TARGET);
    ComponentMask required_comp_target = (1 << COMPONENT_GRIDPOSITION);

    if (!world->game_state.is_paused)
        for (int i = 0; i < MAX_ENTITIES; i++) {
            if (world->entities[i].id == INVALID_ENTITY_ID)
                continue;
            if ((world->entities[i].component_masks & required_comp) != required_comp)
                continue;

            enum EntityTag tag_targetee = world->entities[i].tag;
            int grid_pos_idx = world->entities[i].component_indices[COMPONENT_GRIDPOSITION];
            int target_idx = world->entities[i].component_indices[COMPONENT_TARGET];

            cGridPosition *grid_pos_targetee = &((cGridPosition *)world->component_pools[COMPONENT_GRIDPOSITION].data)[grid_pos_idx];
            cTarget *target = &((cTarget *)world->component_pools[COMPONENT_TARGET].data)[target_idx];

            // Reset target
            target->current_target = INVALID_ENTITY_ID;
            target->target_distance = 10000;
            target->is_active = false;
            target->is_new = false;

            for (int j = 0; j < MAX_ENTITIES; j++) {
                if (world->entities[j].id == INVALID_ENTITY_ID)
                    continue;
                if ((world->entities[j].component_masks & required_comp_target) == 0)
                    continue;

                /*The entity "i" can target entity "j" then move on with targeting*/
                enum EntityTag tag_target = world->entities[j].tag;
                if (can_target(tag_targetee, tag_target) == false) {
                    continue;
                }

                int grid_pos_idx = world->entities[j].component_indices[COMPONENT_GRIDPOSITION];
                cGridPosition *grid_pos_target = &((cGridPosition *)world->component_pools[COMPONENT_GRIDPOSITION].data)[grid_pos_idx];

                float temp_target_distance = distance(grid_pos_targetee->x, grid_pos_targetee->y, grid_pos_target->x, grid_pos_target->y);

                if (target->target_distance > temp_target_distance) {
                    target->target_distance = temp_target_distance;
                    target->current_target = world->entities[j].id;
                    target->is_active = true;
                }
            }
        }
    PROFILE_END("System Targeting");
}
