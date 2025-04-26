#include "entity.h"
#include "string.h"


int create_entity(World *world) {
    int id;
    if (world->free_id_count > 0) {
        id = world->free_ids[--world->free_id_count];
        world->free_ids[world->free_id_count] = INVALID_ENTITY_ID;
    } else {
        if (world->entity_count >= MAX_ENTITIES) return INVALID_ENTITY_ID;
        id = world->entity_count++;
    }

    world->entities[id].id = id;
    for (int i = 0; i < NUM_COMPONENT_TYPES; i++) {
        world->entities[id].component_indices[i] = INVALID_COMPONENT_INDEX;
    }

    return id;
}


void destroy_entity(World *world, int entity_id) {
    if (entity_id < 0 || entity_id >= MAX_ENTITIES || world->entities[entity_id].id == INVALID_ENTITY_ID) return;

    for (int i = 0; i < NUM_COMPONENT_TYPES; i++) {
        int index = world->entities[entity_id].component_indices[i];
        if (index != INVALID_COMPONENT_INDEX) {
            memset((char*)world->component_pools->data + index * world->component_pools->component_size, 0, world->component_pools->component_size);
            if (world->component_pools->free_count < MAX_ENTITIES) {
                world->component_pools->free_ids[world->component_pools->free_count++] = index;
            }
            world->component_pools->active_count--;
            world->entities[entity_id].component_indices[i] = INVALID_COMPONENT_INDEX;
        }
    }

    world->entities[entity_id].id = INVALID_ENTITY_ID;

    if (world->free_id_count < MAX_ENTITIES) {
        world->free_ids[world->free_id_count++] = entity_id;
    }
}
