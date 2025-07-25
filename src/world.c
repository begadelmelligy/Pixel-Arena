#include "world.h"
#include "event_handler.h"
#include "helper.h"

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
    initialize_component_pool(world, COMPONENT_ABILITY_CASTER, world->ability_caster, sizeof(cAbilityCaster));
    initialize_component_pool(world, COMPONENT_CAST_REQUEST, world->cast_request, sizeof(cCastRequest));
    initialize_component_pool(world, COMPONENT_SPRITE, world->sprite, sizeof(cSprite));

    initialize_keys(world);
    initialize_grid(world);
    initialize_debug_mode_parameters(world);

    world->adj_para.scroll_summon_spacing = 50;

    init_sprite_manager(&world->sprite_manager);
    init_event_handler(&world->event_handler);

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

void remove_component(World *world, int entity_id, int component_type)
{
    if (entity_id < 0 || entity_id >= MAX_ENTITIES || world->entities[entity_id].id == INVALID_ENTITY_ID)
        return;

    if (component_type < 0 || component_type >= NUM_COMPONENT_TYPES)
        return;

    int index_to_remove = world->entities[entity_id].component_indices[component_type];
    if (index_to_remove == INVALID_COMPONENT_INDEX)
        return;

    ComponentPool *pool = &world->component_pools[component_type];

    if (component_type == COMPONENT_PATH) {
        void *component_data = (char *)pool->data + index_to_remove * pool->component_size;
        freePath(component_data);
    }

    if (component_type == COMPONENT_ABILITY_CASTER) {
        void *component_data = (char *)pool->data + index_to_remove * pool->component_size;
        freePath(component_data);
        dictFree(&get_ability_caster(world, entity_id)->abilities);
    }

    if (index_to_remove < pool->active_count - 1) {
        void *dest = (char *)pool->data + index_to_remove * pool->component_size;
        void *src = (char *)pool->data + (pool->active_count - 1) * pool->component_size;
        memcpy(dest, src, pool->component_size);

        for (int i = 0; i < MAX_ENTITIES; i++) {
            if (world->entities[i].id != INVALID_ENTITY_ID &&
                world->entities[i].component_indices[component_type] == pool->active_count - 1) {
                // Update the component index
                world->entities[i].component_indices[component_type] = index_to_remove;
                break;
            }
        }
    }

    pool->active_count--;

    world->entities[entity_id].component_indices[component_type] = INVALID_COMPONENT_INDEX;
    world->entities[entity_id].component_masks &= ~(1 << component_type);
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

cAbilityCaster *get_ability_caster(World *world, int entity_id)
{
    int index = world->entities[entity_id].component_indices[COMPONENT_ABILITY_CASTER];
    if (index == INVALID_COMPONENT_INDEX)
        return NULL;
    return &((cAbilityCaster *)world->component_pools[COMPONENT_ABILITY_CASTER].data)[index];
}

cCastRequest *get_cast_request(World *world, int entity_id)
{
    int index = world->entities[entity_id].component_indices[COMPONENT_CAST_REQUEST];
    if (index == INVALID_COMPONENT_INDEX)
        return NULL;
    return &((cCastRequest *)world->component_pools[COMPONENT_CAST_REQUEST].data)[index];
}

cSprite *get_sprite(World *world, int entity_id)
{
    int index = world->entities[entity_id].component_indices[COMPONENT_SPRITE];
    if (index == INVALID_COMPONENT_INDEX)
        return NULL;
    return &((cSprite *)world->component_pools[COMPONENT_SPRITE].data)[index];
}
