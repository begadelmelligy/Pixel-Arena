#ifndef PROPERTIES_H
#define PROPERTIES_H

typedef enum {
    TYPE_GROUND = 1,
    TYPE_FLYING = 2,
    TYPE_FIRE = 3,
    TYPE_WATER = 4,
    TYPE_WIND = 5,
    TYPE_EARCH = 6,
    TYPE_DARK = 7,
    TYPE_LIGHT = 8,
    NUM_UNIT_TYPE
} UnitType;

typedef enum {
    RARITY_NORMAL = 1,
    RARITY_UNIQUE = 2,
    RARITY_ELITE = 3,
    RARITY_SUPER = 4,
    RARITY_LEGENDARY = 5,
    RARITY_MYTHIC,
} UnitRarity;

typedef struct cProperties {
    UnitType types[NUM_UNIT_TYPE];
    UnitRarity rarity;
    int num_types;
} cProperties;

#endif
