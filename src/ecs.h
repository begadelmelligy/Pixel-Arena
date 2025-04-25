#ifndef ECS_H
#define ECS_H

#include <string.h>
#include "components.h"
#include "globals.h"


/*Add more components here*/
enum ComponentType {
    COMPONENT_POSITION = 0,
    COMPONENT_VELOCITY = 1,
    COMPONENT_HEALTH = 2,
    COMPONENT_PROPERTIES = 3,
};


typedef struct {
    void* data;
    size_t component_size;
    int free_ids[MAX_ENTITIES];
    int free_count;
    int active_count;
} ComponentPool;


void init_ecs(void);
int create_entity(void);
void destroy_entity(int entity_id);
void add_component(int entity_id, int component_type, void* component_data);


cPosition* get_position(int entity_id);
cVelocity* get_velocity(int entity_id);
cHealth* get_health(int entity_id);
cProperties* get_properties(int entity_id);

#endif
