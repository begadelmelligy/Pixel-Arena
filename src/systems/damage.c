#include <stdio.h>
#include "../../systems/damage.h"

DamageEvent damageEvents[MAX_EVENTS];
int damageEventCount = 0;


void queueDamage(int entity, float amount) {
    if (damageEventCount < MAX_EVENTS) {
        damageEvents[damageEventCount++] = (DamageEvent){entity, amount};
    }

}

void applyDamage(World *world, int entity_id, float amount) {
        if (entity_id == INVALID_ENTITY_ID) return;
        int health_idx = world->entities[entity_id].component_indices[COMPONENT_HEALTH];
        if (health_idx != INVALID_COMPONENT_INDEX){
            cHealth* health = &((cHealth*)world->component_pools[COMPONENT_HEALTH].data)[health_idx];


            health->currentHealth -= amount;
            if (health->currentHealth < 0){
                health->currentHealth = 0;
                destroy_entity(world, entity_id);
            }
            printf("Entity %d has taken %f damage\n", world->entities[entity_id].id, amount);
            printf("Remaining life is %f\n\n", health->currentHealth);
        }
}


void sDamage(World *world, float dt){
    (void)dt;
    for (int i = 0; i < damageEventCount; i++) {
        applyDamage(world, damageEvents[i].target, damageEvents[i].amount);
    }

    damageEventCount = 0;
}
