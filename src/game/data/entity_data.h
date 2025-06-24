#ifndef ENTITY_DATA_H
#define ENTITY_DATA_H

#include "../../entity.h"
#include "../../sprite_manager.h"
#include "../../world.h"
#include "ability_data.h"

int summon_test_entity(World *world, SpriteManager *sm, float pos_x, float pos_y);
int summon_enemy_caster(World *world, SpriteManager *sm, float pos_x, float pos_y);

#endif
