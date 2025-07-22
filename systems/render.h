#ifndef RENDER_H
#define RENDER_H

#include "../src/world.h"
#include "../systems/summon.h"

void highlight_summon(World *world, EntityType type, int num_entities, enum Formation formation);
void draw_entities(World *world);
void sRender(World *world, float dt);

#endif
