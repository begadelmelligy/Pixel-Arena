#include "ecs.h"
#include "components.h"
#include <string.h>


Entity entities[MAX_ENTITIES];
int entity_count = 0;

int free_ids[MAX_ENTITIES];
int free_id_count = 0;


ComponentPool component_pools[NUM_COMPONENT_TYPES];

/*Add more components here*/
cPosition positions[MAX_ENTITIES];
cVelocity velocities[MAX_ENTITIES];
cHealth health[MAX_ENTITIES];
cProperties properties[MAX_ENTITIES];


void init_ecs(void) {
    for (int i = 0; i < MAX_ENTITIES; i++) {
        free_ids[i] = INVALID_ENTITY_ID;
    }
    free_id_count = 0;
    entity_count = 0;

    component_pools[COMPONENT_POSITION] = (ComponentPool){
        .data = positions,
        .component_size = sizeof(cPosition),
        .free_count = 0,
        .active_count = 0
    };

    component_pools[COMPONENT_VELOCITY] = (ComponentPool){
        .data = velocities,
        .component_size = sizeof(cVelocity),
        .free_count = 0,
        .active_count = 0
    };

    component_pools[COMPONENT_HEALTH] = (ComponentPool){
        .data = health,
        .component_size = sizeof(cHealth),
        .free_count = 0,
        .active_count = 0
    };

    component_pools[COMPONENT_PROPERTIES] = (ComponentPool){
        .data = properties,
        .component_size = sizeof(cProperties),
        .free_count = 0,
        .active_count = 0
    };


    for (int i = 0; i < MAX_ENTITIES; i++) {
        component_pools[COMPONENT_POSITION].free_ids[i] = INVALID_COMPONENT_INDEX;
        component_pools[COMPONENT_VELOCITY].free_ids[i] = INVALID_COMPONENT_INDEX;
        component_pools[COMPONENT_HEALTH].free_ids[i] = INVALID_COMPONENT_INDEX;
        component_pools[COMPONENT_PROPERTIES].free_ids[i] = INVALID_COMPONENT_INDEX;
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


cPosition* get_position(int entity_id) {
    int index = entities[entity_id].component_indices[COMPONENT_POSITION];
    if (index == INVALID_COMPONENT_INDEX) return NULL;
    return &((cPosition*)component_pools[COMPONENT_POSITION].data)[index];
}


cVelocity* get_velocity(int entity_id) {
    int index = entities[entity_id].component_indices[COMPONENT_VELOCITY];
    if (index == INVALID_COMPONENT_INDEX) return NULL;
    return &((cVelocity*)component_pools[COMPONENT_VELOCITY].data)[index];
}


cHealth* get_health(int entity_id) {
    int index = entities[entity_id].component_indices[COMPONENT_HEALTH];
    if (index == INVALID_COMPONENT_INDEX) return NULL;
    return &((cHealth*)component_pools[COMPONENT_HEALTH].data)[index];
}


cProperties* get_properties(int entity_id) {
    int index = entities[entity_id].component_indices[COMPONENT_PROPERTIES];
    if (index == INVALID_COMPONENT_INDEX) return NULL;
    return &((cProperties*)component_pools[COMPONENT_PROPERTIES].data)[index];
}
