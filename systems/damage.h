#ifndef DAMAGE_H
#define DAMAGE_H


typedef struct{
    int target;
    float amount;
} DamageEvent;

struct World;


void queueDamage(int entity, float amount);
void applyDamage(struct World *world, int entity, float amount);
void sDamage(void);

#endif
