#ifndef SYSTEMS_H
#define SYSTEMS_H


void sMovement(float delta);
void queueDamage(int entity, float amount);
void applyDamage(int entity, float amount);
void sDamage();
void sRender();


typedef struct{
    int target;
    float amount;
} DamageEvent;


#endif // SYSTEMS_H
