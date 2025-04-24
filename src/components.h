#ifndef COMPONENTS_H
#define COMPONENTS_H

typedef struct {
    float x, y;
} Position;


typedef struct {
    float dx, dy;
} Velocity;


typedef struct {
    float maxHealth;
    float currentHealth;
} Health;


typedef struct {
    float maxMana;
    float currentMana;
} Mana;


typedef struct {
    float maxStamina;
    float currentStamina;
} Stamina;

#endif
