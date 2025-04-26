#ifndef ENTITY_H
#define ENTITY_H

#include "globals.h"
#include "world.h"


int create_entity(World *world);
void destroy_entity(World *world, int entity_id);

#endif
