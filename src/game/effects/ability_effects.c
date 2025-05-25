#include "ability_effects.h"
#include <stdio.h>

void cast_fireball(void *w, int caster, int target)
{
    World *world = (World *)w;

    printf("Casting Fireball - Caster: %d, Target: %d\n", caster, target);
}

void cast_chain_lightning(void *w, int caster, int target)
{
    World *world = (World *)w;

    printf("Casting Chain Lightning - Caster: %d, Target: %d\n", caster, target);
}
