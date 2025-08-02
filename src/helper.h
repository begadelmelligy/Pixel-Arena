#ifndef HELPER_H
#define HELPER_H

#include "world.h"

extern const char *ComponentTypeName[];

void initialize_component_pool(World *world, enum ComponentType type, void *data, size_t component_size);
void initialize_keys(World *world);
void initialize_grid(World *world);

void initialize_debug_mode_parameters(World *world);

const char *get_component_type_name(enum ComponentType type);

#endif
