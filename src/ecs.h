#ifndef ECS_H
#define ECS_H

#include "globals.h"
#include "stdint.h"
#include "world.h"

typedef uint32_t SystemID;

void init_ecs(void);
SystemID ecs_register_system(void (*system)(World *, float));
void ecs_update(World *world, float delta_time);

#endif
