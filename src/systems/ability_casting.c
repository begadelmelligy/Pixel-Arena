#include "../../systems/ability_casting.h"
#include "../dev_tools/profiler.h"
#include "../game/data/ability_data.h"

void sAbilityCasting(World *world, float dt)
{
    PROFILE_BEGIN("System AbilityCasting");
    (void)dt;
    ComponentMask required_comp = (1 << COMPONENT_ABILITY_CONTAINER) | (1 << COMPONENT_CAST_REQUEST) | (1 << COMPONENT_AISTATE);

    if (!world->game_state.is_paused) {
        for (int i = 0; i < MAX_ENTITIES; i++) {

            if (world->entities[i].id == INVALID_ENTITY_ID)
                continue;
            if ((world->entities[i].component_masks & required_comp) != required_comp)
                continue;

            int ability_container_idx = world->entities[i].component_indices[COMPONENT_ABILITY_CONTAINER];
            int cast_request_idx = world->entities[i].component_indices[COMPONENT_CAST_REQUEST];
            int aistate_idx = world->entities[i].component_indices[COMPONENT_AISTATE];

            cAbilityContainer *ability_container =
                &((cAbilityContainer *)world->component_pools[COMPONENT_ABILITY_CONTAINER].data)[ability_container_idx];
            cCastRequest *cast_request = &((cCastRequest *)world->component_pools[COMPONENT_CAST_REQUEST].data)[cast_request_idx];
            cAIState *aistate = &((cAIState *)world->component_pools[COMPONENT_AISTATE].data)[aistate_idx];

            if (cast_request->is_active == false) {
                continue;
            }

            /*switch the aistate to CASTING*/
            enum AIState to_state = STATE_CASTING;
            bool can_transition = transition(aistate, to_state);

            if (can_transition) {
                /*cast the ability that is requested via the ability picker */
                Ability ability = all_abilities[cast_request->ability_id];
                ability.cast_function(&world, world->entities[i].id, cast_request->target);

                ability_container->is_casting = true;
                ability_container->remaining_cast_time = ability.cast_time;

                float cd = ability.cooldown;
                dictUpdateValue(&ability_container->remaining_cd, cast_request->ability_id, &cd);

                cast_request->is_active = false;
            }
        }
    }
    PROFILE_END("System AbilityCasting");
}
