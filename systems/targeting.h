#ifndef TARGETING_H
#define TARGETING_H

#include "../src/world.h"

void sTargeting(World *world, float dt);
bool can_target(enum EntityTag targetee, enum EntityTag target);

#endif
