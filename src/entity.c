#include "entity.h"
#include "string.h"

int free_ids[MAX_ENTITIES];
int free_id_count = 0;

Entity entities[MAX_ENTITIES];
int entity_count = 0;


int create_entity(void) {
    int id;
    if (free_id_count > 0) {
        id = free_ids[--free_id_count];
        free_ids[free_id_count] = INVALID_ENTITY_ID;
    } else {
        if (entity_count >= MAX_ENTITIES) return INVALID_ENTITY_ID;
        id = entity_count++;
    }

    entities[id].id = id;
    for (int i = 0; i < NUM_COMPONENT_TYPES; i++) {
        entities[id].component_indices[i] = INVALID_COMPONENT_INDEX;
    }

    return id;
}


void destroy_entity(int entity_id, World *world) {
    if (entity_id < 0 || entity_id >= MAX_ENTITIES || entities[entity_id].id == INVALID_ENTITY_ID) return;

    for (int i = 0; i < NUM_COMPONENT_TYPES; i++) {
        int index = entities[entity_id].component_indices[i];
        if (index != INVALID_COMPONENT_INDEX) {
            memset((char*)world->component_pools->data + index * world->component_pools->component_size, 0, world->component_pools->component_size);
            if (world->component_pools->free_count < MAX_ENTITIES) {
                world->component_pools->free_ids[world->component_pools->free_count++] = index;
            }
            world->component_pools->active_count--;
            entities[entity_id].component_indices[i] = INVALID_COMPONENT_INDEX;
        }
    }

    entities[entity_id].id = INVALID_ENTITY_ID;

    if (free_id_count < MAX_ENTITIES) {
        free_ids[free_id_count++] = entity_id;
    }
}
