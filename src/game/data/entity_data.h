#ifndef ENTITY_DATA_H
#define ENTITY_DATA_H

#include "../../entity.h"
#include "../../world.h"
#include "ability_data.h"
#include "raylib.h"

#define ENTITY_TYPE_COUNT 2

typedef enum EntityType {
    LIGHT_WIZARD = 0,
    DARK_WIZARD = 1,
} EntityType;

extern cSprite all_entitites_types[ENTITY_TYPE_COUNT];

int summon_test_entity(World *world, float pos_x, float pos_y);
int summon_enemy_caster(World *world, float pos_x, float pos_y);

#endif
