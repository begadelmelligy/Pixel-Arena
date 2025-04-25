#ifndef SYSTEMS_H
#define SYSTEMS_H

#include "components.h"

void queueDamage(int entity, float amount);
void applyDamage(int entity, float amount);

void spawnUnits(int quantity, float pos_x, float pos_y, float max_health, UnitRarity rarity, int num_types, UnitType *types);


void sMovement(float delta);
void sDamage();
void sRender();


typedef struct{
    int target;
    float amount;
} DamageEvent;


#endif // SYSTEMS_H
