#ifndef HELPER_H
#define HELPER_H

#include "world.h"

void initialize_component_pool(World *world, enum ComponentType type, void *data, size_t component_size);
void initialize_keys(World *world);

#endif
