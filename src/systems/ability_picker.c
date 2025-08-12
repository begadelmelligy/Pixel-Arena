#include "../../systems/ability_picker.h"
#include "../dev_tools/profiler.h"
#include "../game/data/ability_data.h"
#include <stdio.h>

void sAbilityPicker(World *world, float dt)
{
    PROFILE_BEGIN("System AbilityPicker");
    ComponentMask required_comp = (1 << COMPONENT_ABILITY_CONTAINER) | (1 << COMPONENT_CAST_REQUEST) |
                                  (1 << COMPONENT_TARGET) | (1 << COMPONENT_AISTATE);

    if (!world->game_state.is_paused) {
        for (int i = 0; i < MAX_RESTRICTED_ENTITIES; i++) {

            if (world->entities[i].id == INVALID_ENTITY_ID)
                continue;
            if ((world->entities[i].component_masks & required_comp) == 0)
                continue;

            int ability_container_idx = world->entities[i].component_indices[COMPONENT_ABILITY_CONTAINER];
            int cast_request_idx = world->entities[i].component_indices[COMPONENT_CAST_REQUEST];
            int target_idx = world->entities[i].component_indices[COMPONENT_TARGET];
            int aistate_idx = world->entities[i].component_indices[COMPONENT_AISTATE];

            cAbilityContainer *ability_container =
                &((cAbilityContainer *)world->component_pools[COMPONENT_ABILITY_CONTAINER].data)[ability_container_idx];
            cCastRequest *cast_request =
                &((cCastRequest *)world->component_pools[COMPONENT_CAST_REQUEST].data)[cast_request_idx];
            cTarget *target = &((cTarget *)world->component_pools[COMPONENT_TARGET].data)[target_idx];
            cAIState *aistate = &((cAIState *)world->component_pools[COMPONENT_AISTATE].data)[aistate_idx];

            if (target->current_target == INVALID_ENTITY_ID) {
                continue;
            }

            /*Reduce the remaining cast time and continue the loop*/
            if (ability_container->is_casting == true) {
                ability_container->remaining_cast_time -= dt;
                if (ability_container->remaining_cast_time <= 0) {
                    ability_container->is_casting = false;
                    enum AIState to_state = STATE_IDLE;
                    transition(aistate, to_state);
                    /*printf("Current: %d, Next: %d\n", aistate->current_state, aistate->next_state);*/
                }
                /*printf("Remaning Cast Time: %f\n", ability_container->remaining_cast_time);*/
                continue;
            }

            /*Available abilities based on off cd*/
            AbilityID ability_to_cast = ABILITY_NONE;
            enum AbilityPriority ability_priority = PRIORITY_NONE;

            if (ability_container->ability_count > 0) {
                for (int j = 0; j < ability_container->ability_count; j++) {
                    if (*(float *)ability_container->remaining_cd.entries[j].value == 0.0f) {
                        Ability current_ability = all_abilities[*(int *)ability_container->abilities.entries[j].value];
                        if (ability_priority < current_ability.priority) {
                            ability_to_cast = current_ability.ability_id;
                        }
                    }
                }
            }

            if (ability_to_cast == ABILITY_NONE) {
                continue;
            }

            *cast_request = (cCastRequest){
                .ability_id = ability_to_cast,
                .target = target->current_target,
                .is_active = true,
            };
            /*printf("Requested to Cast Ability: %d\n", cast_request->ability_id);*/
        }
    }
    PROFILE_END("System AbilityPicker");
}
