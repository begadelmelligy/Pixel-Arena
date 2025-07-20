#ifndef DAMAGE_H
#define DAMAGE_H

#include "../src/entity.h"
#include "../src/world.h"

typedef struct {
    int target;
    float amount;
} DamageEvent;

void queue_damage(int entity, float amount);
void apply_damage(World *world, int entity, float amount);
void sDamage(World *world, float dt);

#endif
