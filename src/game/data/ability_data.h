#ifndef ABILITY_DATA_H
#define ABILITY_DATA_H

#include "../../../components/ability.h"

#define ABILITY_COUNT 3

typedef enum {
    ABILITY_NONE = 0,
    ABILITY_FIREBALL = 1,
    ABILITY_CHAIN_LIGHTNING = 2,
} AbilityID;

extern Ability all_abilities[ABILITY_COUNT];

#endif
