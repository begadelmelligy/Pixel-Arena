#ifndef WORLD_H
#define WORLD_H

#include "ecs.h"

#include "../components/velocity.h"
#include "../components/position.h"
#include "../components/health.h"
#include "../components/properties.h"

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


typedef struct {
    cPosition positions[MAX_ENTITIES];
    cVelocity velocities[MAX_ENTITIES];
    cHealth health[MAX_ENTITIES];
    cProperties properties[MAX_ENTITIES];
    ComponentPool *component_pools;
} World;



World *create_world(void);
void destroy_world(World *world);

void add_component(int entity_id, int component_type, void* component_data);

cPosition* get_position(int entity_id, World *world);
cVelocity* get_velocity(int entity_id, World *world);
cHealth* get_health(int entity_id, World *world);
cProperties* get_properties(int entity_id, World *world);

#endif
