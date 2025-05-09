#ifndef PROPERTIES_H
#define PROPERTIES_H

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

typedef enum { NORMAL, UNIQUE, ELITE, SUPER, LEGENDARY, MYTHIC } UnitRarity;

typedef struct cProperties {
  UnitType types[NUM_UNIT_TYPE];
  UnitRarity rarity;
  int num_types;
} cProperties;

#endif
