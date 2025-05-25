#include "entity.h"
#include "ds.h"
#include "globals.h"
#include "string.h"
#include "world.h"

int create_entity(World *world)
{
    int id;
    if (world->free_id_count > 0) {
        id = world->free_ids[--world->free_id_count];
        world->free_ids[world->free_id_count] = INVALID_ENTITY_ID;

    } else {
        if (world->entity_count >= MAX_ENTITIES)
            return INVALID_ENTITY_ID;

        id = world->entity_count++;
    }

    world->entities[id].id = id;
    world->entities[id].component_masks = 0;
    world->entities[id].tag_mask = 0;

    for (int i = 0; i < NUM_COMPONENT_TYPES; i++) {
        world->entities[id].component_indices[i] = INVALID_COMPONENT_INDEX;
    }

    return id;
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

void destroy_entity(World *world, int entity_id)
{
    if (entity_id < 0 || entity_id >= MAX_ENTITIES || world->entities[entity_id].id == INVALID_ENTITY_ID)
        return;

    for (int i = 0; i < NUM_COMPONENT_TYPES; i++) {
        if (world->entities[entity_id].component_indices[i] != INVALID_COMPONENT_INDEX) {
            remove_component(world, entity_id, i);
        }
    }

    world->entities[entity_id].id = INVALID_ENTITY_ID;
    world->entities[entity_id].tag_mask = 0;
    world->entities[entity_id].component_masks = 0;

    if (world->free_id_count < MAX_ENTITIES) {
        world->free_ids[world->free_id_count++] = entity_id;
    }
}
