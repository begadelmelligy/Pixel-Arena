#ifndef RENDER_H
#define RENDER_H

#include "../components/position.h"
#include "../src/entity_debugger.h"
#include "../src/globals.h"
#include "../src/helper.h"
#include "../src/world.h"
#include "../systems/summon.h"

void highlight_summon(World *world, EntityType type, int num_entities, enum Formation formation);
void sRender(World *world, float dt);

#endif
