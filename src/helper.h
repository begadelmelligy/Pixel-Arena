#ifndef HELPER_H
#define HELPER_H

#include "globals.h"
#include "world.h"

void initialize_component_pool(World *world, enum ComponentType type, void *data, size_t component_size);
void initialize_keys(World *world);
void initialize_grid(World *world);


//#TODO: create these functions.
cGridPosition world_pos_to_grid_pos(Entity entity_id, cPosition curr_pos);
cPosition grid_pos_to_world_pos(Entity entity_id, cGridPosition curr_grid_pos);

void debug_draw_grid(World *world);


#endif
