#include <stdio.h>
#include "../../systems/damage.h"

#include "../ecs.h"
#include "../entity.c"

DamageEvent damageEvents[MAX_EVENTS];
int damageEventCount = 0;


void queueDamage(int entity, float amount) {
    if (damageEventCount < MAX_EVENTS) {
        damageEvents[damageEventCount++] = (DamageEvent){entity, amount};
    }

}

void applyDamage(World *world, int entity_id, float amount) {
        if (entity_id == INVALID_ENTITY_ID) return;
        int health_idx = entities[entity_id].component_indices[COMPONENT_HEALTH];
        if (health_idx != INVALID_COMPONENT_INDEX){
            cHealth* health = &((cHealth*)world->component_pools[COMPONENT_HEALTH].data)[health_idx];


            health->currentHealth -= amount;
            if (health->currentHealth < 0){
                health->currentHealth = 0;
            }
            printf("Entity %d has taken %f damage\n", entities[entity_id].id, amount);
            printf("Remaining life is %f\n\n", health->currentHealth);
        }
}


void sDamage(void){
    for (int i = 0; i < damageEventCount; i++) {
        applyDamage(damageEvents[i].target, damageEvents[i].amount);
    }

    damageEventCount = 0;
}
