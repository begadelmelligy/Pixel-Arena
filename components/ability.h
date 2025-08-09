#ifndef ABILITY_H
#define ABILITY_H

#include "../src/support/ds.h"
#include "stdbool.h"

enum AbilityPriority {
    PRIORITY_NONE = 0,
    PRIORITY_LOW = 1,
    PRIORITY_NORMAL = 2,
    PRIORITY_MEDIUM = 3,
    PRIORITY_HIGH = 4,
    PRIORITY_ULTIMATE = 5,
};

typedef struct Ability {
    int ability_id;
    enum AbilityPriority priority;
    float range;
    float cooldown;
    float cast_time;
    bool requires_target;
    void (*cast_function)(void *world, int caster, int target);
} Ability;

typedef struct cAbilityContainer {
    int ability_count;
    Dict abilities;
    Dict remaining_cd;
    float remaining_cast_time;
    bool is_casting;
} cAbilityContainer;

typedef struct cCastRequest {
    int ability_id;
    int target;
    bool is_active;
} cCastRequest;

#endif
