#include "../../systems/ability_casting.h"
#include "../game/data/ability_data.h"

void sAbilityCasting(World *world, float dt)
{
    (void)dt;
    ComponentMask required_comp = (1 << COMPONENT_ABILITY_CASTER) | (1 << COMPONENT_CAST_REQUEST);

    if (!world->game_state.is_paused) {
        for (int i = 0; i < MAX_ENTITIES; i++) {

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

            /*Loop over all the abilities*/
            /*If not on CD and not currently casting then cast and return*/
            Ability ability = all_abilities[cast_request->ability_id];

            if (ability_caster->)
        }
    }
}
