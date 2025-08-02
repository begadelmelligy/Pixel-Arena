#include "../../systems/ability_casting.h"
#include "../dev_tools/profiler.h"
#include "../game/data/ability_data.h"
#include <stdio.h>

void sAbilityCasting(World *world, float dt)
{
    PROFILE_BEGIN("System AbilityCasting");
    (void)dt;
    ComponentMask required_comp = (1 << COMPONENT_ABILITY_CASTER) | (1 << COMPONENT_CAST_REQUEST);

    if (!world->game_state.is_paused) {
        for (int i = 0; i < MAX_RESTRICTED_ENTITIES; i++) {

            if (world->entities[i].id == INVALID_ENTITY_ID)
                continue;
            if ((world->entities[i].component_masks & required_comp) == 0)
                continue;

            int ability_caster_idx = world->entities[i].component_indices[COMPONENT_ABILITY_CASTER];
            int cast_request_idx = world->entities[i].component_indices[COMPONENT_CAST_REQUEST];

            cAbilityCaster *ability_caster =
                &((cAbilityCaster *)world->component_pools[COMPONENT_ABILITY_CASTER].data)[ability_caster_idx];
            cCastRequest *cast_request =
                &((cCastRequest *)world->component_pools[COMPONENT_CAST_REQUEST].data)[cast_request_idx];

            if (!cast_request->is_active) {
                continue;
            }

            float *remaining_cd = (float *)dictGet(&ability_caster->remaining_cd, cast_request->ability_id);
            printf("remain: %f\n", *remaining_cd);
            if (*remaining_cd > 0 || ability_caster->is_casting) {
                continue;
            }

            Ability ability = all_abilities[cast_request->ability_id];
            ability.cast_function(&world, world->entities[i].id, cast_request->target);
            ability_caster->is_casting = true;
            ability_caster->remaining_cast_time = ability.cast_time;

            float cd = ability.cooldown;
            dictUpdateValue(&ability_caster->remaining_cd, cast_request->ability_id, &cd);

            cast_request->is_active = false;
        }
    }
    PROFILE_END("System AbilityCasting");
}
