#include "ability_data.h"
#include "../effects/ability_effects.h"

Ability all_abilities[ABILITY_COUNT] = {
    [ABILITY_FIREBALL] =
        {
            .ability_id = ABILITY_FIREBALL,
            .priority = PRIORITY_ULTIMATE,
            .range = 100,
            .cooldown = 15.0f,
            .cast_time = 0.5f,
            .requires_target = true,
            .cast_function = cast_fireball,
        },

    [ABILITY_CHAIN_LIGHTNING] =
        {
            .ability_id = ABILITY_CHAIN_LIGHTNING,
            .priority = PRIORITY_MEDIUM,
            .range = 200,
            .cooldown = 5.0f,
            .cast_time = 0.2f,
            .requires_target = true,
            .cast_function = cast_chain_lightning,
        },
};
