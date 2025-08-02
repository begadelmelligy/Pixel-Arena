#include "../../systems/damage.h"
#include "../entity.h"
#include "../profiler.h"
#include <stdio.h>

DamageEvent damage_events[MAX_EVENTS];
int damage_event_count = 0;

void queue_damage(int entity, float amount)
{
    if (damage_event_count < MAX_EVENTS) {
        damage_events[damage_event_count++] = (DamageEvent){entity, amount};
    }
}

void apply_damage(World *world, int entity_id, float amount)
{
    if (entity_id == INVALID_ENTITY_ID)
        return;
    int health_idx = world->entities[entity_id].component_indices[COMPONENT_HEALTH];
    if (health_idx != INVALID_COMPONENT_INDEX) {
        cHealth *health = &((cHealth *)world->component_pools[COMPONENT_HEALTH].data)[health_idx];

        health->current_health -= amount;
        if (health->current_health < 0) {
            health->current_health = 0;
            destroy_entity(world, entity_id);
        }
        printf("Entity %d has taken %f damage\n", world->entities[entity_id].id, amount);
        printf("Remaining life is %f\n\n", health->current_health);
    }
}

void sDamage(World *world, float dt)
{
    PROFILE_BEGIN("System Damage");
    (void)dt;

    if (!world->game_state.is_paused) {
        for (int i = 0; i < damage_event_count; i++) {
            apply_damage(world, damage_events[i].target, damage_events[i].amount);
        }

        damage_event_count = 0;
    }
    PROFILE_END("System Damage");
}
