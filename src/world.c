#include "world.h"
#include "globals.h"
#include "helper.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

World *create_world(void)
{
    World *world = malloc(sizeof(World));

    world->component_pools = malloc(NUM_COMPONENT_TYPES * sizeof(ComponentPool));

    for (int i = 0; i < MAX_ENTITIES; i++) {
        world->entities[i].id = INVALID_ENTITY_ID;
        world->free_ids[i] = INVALID_ENTITY_ID;
    }

    world->free_id_count = 0;
    world->entity_count = 0;

    /*Add compoenents here and updte every argument*/
    initialize_component_pool(world, COMPONENT_POSITION, world->positions, sizeof(cPosition));
    initialize_component_pool(world, COMPONENT_GRIDPOSITION, world->grid_position, sizeof(cGridPosition));
    initialize_component_pool(world, COMPONENT_VELOCITY, world->velocities, sizeof(cVelocity));
    initialize_component_pool(world, COMPONENT_HEALTH, world->health, sizeof(cHealth));
    initialize_component_pool(world, COMPONENT_PROPERTIES, world->properties, sizeof(cProperties));
    initialize_component_pool(world, COMPONENT_PATH, world->path, sizeof(cPath));
    initialize_component_pool(world, COMPONENT_TARGET, world->target, sizeof(cTarget));
    initialize_component_pool(world, COMPONENT_AISTATE, world->ai_state, sizeof(cAIState));

    initialize_keys(world);
    initialize_grid(world);

    return world;
}

void add_component(World *world, int entity_id, int component_type, void *component_data)
{
    if (entity_id < 0 || entity_id >= MAX_ENTITIES || world->entities[entity_id].id == INVALID_ENTITY_ID)
        return;

    if (component_type < 0 || component_type >= NUM_COMPONENT_TYPES)
        return;

    if (world->entities[entity_id].component_indices[component_type] != INVALID_COMPONENT_INDEX)
        return;

    ComponentPool *pool = &world->component_pools[component_type];

    int index;

    if (pool->free_count > 0) {
        index = pool->free_ids[--pool->free_count];
        pool->free_ids[pool->free_count] = INVALID_COMPONENT_INDEX;

    } else {
        if (pool->active_count >= MAX_ENTITIES)
            return;
        index = pool->active_count++;
    }

    memcpy((char *)pool->data + index * pool->component_size, component_data, pool->component_size);
    world->entities[entity_id].component_indices[component_type] = index;
    world->entities[entity_id].component_masks |= (1 << component_type);
}

void destroy_world(World *world)
{
    if (!world)
        return;
    free(world);
}

cPosition *get_position(World *world, int entity_id)
{
    int index = world->entities[entity_id].component_indices[COMPONENT_POSITION];
    if (index == INVALID_COMPONENT_INDEX)
        return NULL;
    return &((cPosition *)world->component_pools[COMPONENT_POSITION].data)[index];
}

cVelocity *get_velocity(World *world, int entity_id)
{
    int index = world->entities[entity_id].component_indices[COMPONENT_VELOCITY];
    if (index == INVALID_COMPONENT_INDEX)
        return NULL;
    return &((cVelocity *)world->component_pools[COMPONENT_VELOCITY].data)[index];
}

cHealth *get_health(World *world, int entity_id)
{
    int index = world->entities[entity_id].component_indices[COMPONENT_HEALTH];
    if (index == INVALID_COMPONENT_INDEX)
        return NULL;
    return &((cHealth *)world->component_pools[COMPONENT_HEALTH].data)[index];
}

cProperties *get_properties(World *world, int entity_id)
{
    int index = world->entities[entity_id].component_indices[COMPONENT_PROPERTIES];
    if (index == INVALID_COMPONENT_INDEX)
        return NULL;
    return &((cProperties *)world->component_pools[COMPONENT_PROPERTIES].data)[index];
}

cGridPosition *get_grid_position(World *world, int entity_id)
{
    int index = world->entities[entity_id].component_indices[COMPONENT_GRIDPOSITION];
    if (index == INVALID_COMPONENT_INDEX)
        return NULL;
    return &((cGridPosition *)world->component_pools[COMPONENT_GRIDPOSITION].data)[index];
}

cPath *get_path(World *world, int entity_id)
{
    int index = world->entities[entity_id].component_indices[COMPONENT_PATH];
    if (index == INVALID_COMPONENT_INDEX)
        return NULL;
    return &((cPath *)world->component_pools[COMPONENT_PATH].data)[index];
}

cTarget *get_target(World *world, int entity_id)
{
    int index = world->entities[entity_id].component_indices[COMPONENT_TARGET];
    if (index == INVALID_COMPONENT_INDEX)
        return NULL;
    return &((cTarget *)world->component_pools[COMPONENT_TARGET].data)[index];
}

cAIState *get_ai_state(World *world, int entity_id)
{
    int index = world->entities[entity_id].component_indices[COMPONENT_AISTATE];
    if (index == INVALID_COMPONENT_INDEX)
        return NULL;
    return &((cAIState *)world->component_pools[COMPONENT_AISTATE].data)[index];
}
