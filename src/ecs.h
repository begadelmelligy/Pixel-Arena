#ifndef ECS_H
#define ECS_H

#include "stdint.h"


#define MAX_ENTITIES 1000
#define MAX_EVENTS 1000
#define NUM_COMPONENT_TYPES 4
#define INVALID_ENTITY_ID -1
#define INVALID_SYSTEM -1
#define INVALID_COMPONENT_INDEX -1


typedef uint32_t SystemID ;
struct World;


void init_ecs(void);
SystemID ecs_register_system(void (*system) (struct World *, float));
void ecs_update(struct World *world, float delta_time);



#endif
