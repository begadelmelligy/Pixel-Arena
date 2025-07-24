#ifndef SUMMON_H
#define SUMMON_H

#include "../src/game/data/entity_data.h"
#include "../src/world.h"

void summon_entities(World *world, SummonEvent summon_event);
void sSummon(World *world, float dt);

#endif
