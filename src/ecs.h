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
    void* data;                // Array of component data (e.g., Position[MAX_ENTITIES])
    size_t component_size;     // Size of one component (e.g., sizeof(Position))
    int free_ids[MAX_ENTITIES]; // Free list for component slots
    int free_count;            // Number of free slots
    int active_count;          // Number of active components
} ComponentPool;


typedef struct {
    int id;
    int component_indices[NUM_COMPONENT_TYPES];
} Entity;


void init_ecs(void);
int create_entity(void);
void destroy_entity(int entity_id);
void add_position(int entity_id, float x, float y);
void add_velocity(int entity_id, float dx, float dy);

#endif
