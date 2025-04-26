#ifndef DAMAGE_H
#define DAMAGE_H

#include "../src/world.h"


typedef struct{
    int target;
    float amount;
} DamageEvent;


void queueDamage(int entity, float amount);
void applyDamage(World *world, int entity, float amount);
void sDamage(World *world, float dt);

#endif
