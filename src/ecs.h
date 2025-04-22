#ifndef ECS_H
#define ECS_H

#include <string.h>
#include "components.h"

#define MAX_ENTITIES 1000
#define NUM_COMPONENT_TYPES 2
#define INVALID_ENTITY_ID -1
#define INVALID_COMPONENT_INDEX -1


enum ComponentType {
    COMPONENT_POSITION = 0,
    COMPONENT_VELOCITY = 1
};


typedef struct {
    void* data;
    size_t component_size;
    int free_ids[MAX_ENTITIES];
    int free_count;
    int active_count;
} ComponentPool;


typedef struct {
    int id;
    int component_indices[NUM_COMPONENT_TYPES];
} Entity;


void init_ecs(void);
int create_entity(void);
void destroy_entity(int entity_id);


void add_component(int entity_id, int component_type, void* component_data);
Position* get_position(int entity_id);
Velocity* get_velocity(int entity_id);

#endif
