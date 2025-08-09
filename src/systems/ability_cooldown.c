#include "../../systems/ability_cooldown.h"
#include "../dev_tools/profiler.h"
#include <stdio.h>

void sAbilityCooldown(World *world, float dt)
{
    PROFILE_BEGIN("System AbilityCooldown");
    ComponentMask required_comp = (1 << COMPONENT_ABILITY_CONTAINER);

    if (!world->game_state.is_paused && world->game_state.game_state == GAME_COMBAT) {
        for (int i = 0; i < MAX_RESTRICTED_ENTITIES; i++) {

            if (world->entities[i].id == INVALID_ENTITY_ID)
                continue;
            if ((world->entities[i].component_masks & required_comp) == 0)
                continue;

            int ability_container_idx = world->entities[i].component_indices[COMPONENT_ABILITY_CONTAINER];

            cAbilityContainer *ability_container =
                &((cAbilityContainer *)world->component_pools[COMPONENT_ABILITY_CONTAINER].data)[ability_container_idx];

            /*current cooldown ticker. Looping over all entries of the cool down dict*/
            if (ability_container->ability_count > 0) {
                for (int j = 0; j < ability_container->ability_count; j++) {
                    float current_cooldown = *(float *)ability_container->remaining_cd.entries[j].value;
                    if (current_cooldown > 0.0f) {
                        current_cooldown -= dt;
                    } else if (current_cooldown < 0.0f) {
                        current_cooldown = 0.0f;
                    }
                    dictUpdateValue(&ability_container->remaining_cd, ability_container->remaining_cd.entries[j].key,
                                    &current_cooldown);
                }
            }
        }
    }
    PROFILE_END("System AbilityCooldown");
}
