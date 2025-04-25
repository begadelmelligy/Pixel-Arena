#include "world.h"
#include "entity.c"
#include <stdlib.h>


World *create_world(void){
    World *world = malloc(sizeof(World));
    for (int i = 0; i < MAX_ENTITIES; i++) {
        free_ids[i] = INVALID_ENTITY_ID;
    }
    free_id_count = 0;
    entity_count = 0;

    world->component_pools[COMPONENT_POSITION] = (ComponentPool){
        .data = world->positions,
        .component_size = sizeof(cPosition),
        .free_count = 0,
        .active_count = 0
    };

    world->component_pools[COMPONENT_VELOCITY] = (ComponentPool){
        .data = world->velocities,
        .component_size = sizeof(cVelocity),
        .free_count = 0,
        .active_count = 0
    };

    world->component_pools[COMPONENT_HEALTH] = (ComponentPool){
        .data = world->health,
        .component_size = sizeof(cHealth),
        .free_count = 0,
        .active_count = 0
    };

    world->component_pools[COMPONENT_PROPERTIES] = (ComponentPool){
        .data = world->properties,
        .component_size = sizeof(cProperties),
        .free_count = 0,
        .active_count = 0
    };


    for (int i = 0; i < MAX_ENTITIES; i++) {
        world->component_pools[COMPONENT_POSITION].free_ids[i] = INVALID_COMPONENT_INDEX;
        world->component_pools[COMPONENT_VELOCITY].free_ids[i] = INVALID_COMPONENT_INDEX;
        world->component_pools[COMPONENT_HEALTH].free_ids[i] = INVALID_COMPONENT_INDEX;
        world->component_pools[COMPONENT_PROPERTIES].free_ids[i] = INVALID_COMPONENT_INDEX;
    }
    return world;
}



cPosition* get_position(int entity_id, World *world) {
    int index = entities[entity_id].component_indices[COMPONENT_POSITION];
    if (index == INVALID_COMPONENT_INDEX) return NULL;
    return &((cPosition*)world->component_pools[COMPONENT_POSITION].data)[index];
}


cVelocity* get_velocity(int entity_id, World *world) {
    int index = entities[entity_id].component_indices[COMPONENT_VELOCITY];
    if (index == INVALID_COMPONENT_INDEX) return NULL;
    return &((cVelocity*)world->component_pools[COMPONENT_VELOCITY].data)[index];
}


cHealth* get_health(int entity_id, World *world) {
    int index = entities[entity_id].component_indices[COMPONENT_HEALTH];
    if (index == INVALID_COMPONENT_INDEX) return NULL;
    return &((cHealth*)world->component_pools[COMPONENT_HEALTH].data)[index];
}


cProperties* get_properties(int entity_id, World *world) {
    int index = entities[entity_id].component_indices[COMPONENT_PROPERTIES];
    if (index == INVALID_COMPONENT_INDEX) return NULL;
    return &((cProperties*)world->component_pools[COMPONENT_PROPERTIES].data)[index];
}
