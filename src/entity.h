#ifndef ENTITY_H
#define ENTITY_H

#include "ecs.h"
#include "world.h"

typedef struct {
    int id;
    int component_indices[NUM_COMPONENT_TYPES];
} Entity;

int create_entity(void);
void destroy_entity(int entity_id, World *world);

#endif
