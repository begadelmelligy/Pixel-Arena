#include "ecs.h"
#include <stdlib.h>
#include <string.h>

Entity entities[MAX_ENTITIES];
int entity_count = 0;
int free_ids[MAX_ENTITIES];
int free_id_count = 0;

ComponentPool component_pools[NUM_COMPONENT_TYPES];

Position positions[MAX_ENTITIES];
Velocity velocities[MAX_ENTITIES];

void init_ecs(void) {
    for (int i = 0; i < MAX_ENTITIES; i++) {
        free_ids[i] = INVALID_ENTITY_ID;
    }
    free_id_count = 0;
    entity_count = 0;

    component_pools[COMPONENT_POSITION] = (ComponentPool){
        .data = positions,
        .component_size = sizeof(Position),
        .free_count = 0,
        .active_count = 0
    };
    component_pools[COMPONENT_VELOCITY] = (ComponentPool){
        .data = velocities,
        .component_size = sizeof(Velocity),
        .free_count = 0,
        .active_count = 0
    };

    for (int i = 0; i < MAX_ENTITIES; i++) {
        component_pools[COMPONENT_POSITION].free_ids[i] = INVALID_COMPONENT_INDEX;
        component_pools[COMPONENT_VELOCITY].free_ids[i] = INVALID_COMPONENT_INDEX;
    }
}

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

void destroy_entity(int entity_id) {
    if (entity_id < 0 || entity_id >= MAX_ENTITIES || entities[entity_id].id == INVALID_ENTITY_ID) return;

    for (int i = 0; i < NUM_COMPONENT_TYPES; i++) {
        int index = entities[entity_id].component_indices[i];
        if (index != INVALID_COMPONENT_INDEX) {
            ComponentPool* pool = &component_pools[i];
            memset((char*)pool->data + index * pool->component_size, 0, pool->component_size);
            if (pool->free_count < MAX_ENTITIES) {
                pool->free_ids[pool->free_count++] = index;
            }
            pool->active_count--;
            entities[entity_id].component_indices[i] = INVALID_COMPONENT_INDEX;
        }
    }

    entities[entity_id].id = INVALID_ENTITY_ID;

    if (free_id_count < MAX_ENTITIES) {
        free_ids[free_id_count++] = entity_id;
    }
}

void add_component(int entity_id, int component_type, void* component_data) {
    if (entity_id < 0 || entity_id >= MAX_ENTITIES || entities[entity_id].id == INVALID_ENTITY_ID) return;
    if (entities[entity_id].component_indices[component_type] != INVALID_COMPONENT_INDEX) return;

    ComponentPool* pool = &component_pools[component_type];
    int index;

    if (pool->free_count > 0) {
        index = pool->free_ids[--pool->free_count];
        pool->free_ids[pool->free_count] = INVALID_COMPONENT_INDEX;
    } else {
        if (pool->active_count >= MAX_ENTITIES) return;
        index = pool->active_count++;
    }

    memcpy((char*)pool->data + index * pool->component_size, component_data, pool->component_size);
    entities[entity_id].component_indices[component_type] = index;
}


Position* get_position(int entity_id) {
    int index = entities[entity_id].component_indices[COMPONENT_POSITION];
    if (index == INVALID_COMPONENT_INDEX) return NULL;
    return &((Position*)component_pools[COMPONENT_POSITION].data)[index];
}

Velocity* get_velocity(int entity_id) {
    int index = entities[entity_id].component_indices[COMPONENT_VELOCITY];
    if (index == INVALID_COMPONENT_INDEX) return NULL;
    return &((Velocity*)component_pools[COMPONENT_VELOCITY].data)[index];
}
