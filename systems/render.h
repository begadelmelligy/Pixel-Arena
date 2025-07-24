#ifndef RENDER_H
#define RENDER_H

#include "../src/world.h"

void draw_entities(World *world);
void sRender(World *world, float dt);
void highlight_summon(World *world, SummonEvent summon_event);

#endif
