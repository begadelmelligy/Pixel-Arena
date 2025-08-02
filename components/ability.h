#ifndef ABILITY_H
#define ABILITY_H

#include "../src/support/ds.h"
#include "stdbool.h"

typedef struct Ability {
    int ability_id;
    float range;
    float cooldown;
    float cast_time;
    bool requires_target;
    void (*cast_function)(void *world, int caster, int target);
} Ability;

typedef struct cAbilityCaster {
    int ability_count;
    Dict abilities;
    Dict remaining_cd;
    float remaining_cast_time;
    bool is_casting;
} cAbilityCaster;

typedef struct cCastRequest {
    int ability_id;
    int target;
    bool is_active;
} cCastRequest;

#endif
