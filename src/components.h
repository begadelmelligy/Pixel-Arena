#ifndef COMPONENTS_H
#define COMPONENTS_H

typedef enum {
    GROUND,
    FLYING,
    FIRE,
    WATER,
    WIND,
    EARCH,
    DARK,
    LIGHT,
    NUM_UNIT_TYPE
} UnitType;


typedef enum {
    NORMAL,
    UNIQUE,
    ELITE,
    SUPER,
    LEGENDARY,
    MYTHIC
} UnitRarity;

typedef struct {
    float x, y;
} cPosition;


typedef struct {
    float dx, dy;
} cVelocity;


typedef struct {
    float maxHealth;
    float currentHealth;
} cHealth;


typedef struct {
    float maxMana;
    float currentMana;
} cMana;


typedef struct {
    float maxStamina;
    float currentStamina;
} cStamina;

typedef struct {
    UnitType types[NUM_UNIT_TYPE];
    UnitRarity rarity;
    int num_types;
} cProperties;


#endif
