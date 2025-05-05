#include "ecs.h"

#define MAX_SYSTEMS 7

static void (*systems[MAX_SYSTEMS])(World*, float);
static SystemID system_count = 0;


void init_ecs(void) {
    system_count = 0;
    for (int i = 0; i < MAX_SYSTEMS; i++) {
        systems[i] = NULL;
    }
}


SystemID ecs_register_system(void (*system)(World*, float)) {
    if (system_count >= MAX_SYSTEMS) {
        return INVALID_SYSTEM;
    }
    systems[system_count] = system;
    return system_count++;
}


void ecs_update(World *world, float delta_time) {
    for (SystemID i = 0; i < system_count; i++) {
        if (systems[i]) {
            systems[i](world, delta_time);
        }
    }
}
