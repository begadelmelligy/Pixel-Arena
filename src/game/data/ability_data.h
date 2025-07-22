#ifndef ABILITY_DATA_H
#define ABILITY_DATA_H

#include "../../../components/ability.h"

#define ABILITY_COUNT 2

typedef enum {
    ABILITY_FIREBALL,
    ABILITY_CHAIN_LIGHTNING,
} AbilityID;

extern Ability all_abilities[ABILITY_COUNT];

#endif
