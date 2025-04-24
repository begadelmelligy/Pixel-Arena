#include "systems.h"
#include "ecs.h"
#include "raylib.h"
#include <stdio.h>


extern Entity entities[MAX_ENTITIES];
extern int entity_count;
extern ComponentPool component_pools[NUM_COMPONENT_TYPES];


DamageEvent damageEvents[MAX_EVENTS];
int damageEventCount = 0;


void queueDamage(int entity, float amount) {
    if (damageEventCount < MAX_EVENTS) {
        damageEvents[damageEventCount++] = (DamageEvent){entity, amount};
    }

}

void applyDamage(int entity_id, float amount) {
        if (entity_id == INVALID_ENTITY_ID) return;
        int health_idx = entities[entity_id].component_indices[COMPONENT_HEALTH];
        if (health_idx != INVALID_COMPONENT_INDEX){
            Health* health = &((Health*)component_pools[COMPONENT_HEALTH].data)[health_idx];


            health->currentHealth -= amount;
            if (health->currentHealth < 0){
                health->currentHealth = 0;
            }
            printf("Entity %d has taken %f damage\n", entities[entity_id].id, amount);
            printf("Remaining life is %f\n\n", health->currentHealth);
        }
}


void sDamage(){
    for (int i = 0; i < damageEventCount; i++) {
        applyDamage(damageEvents[i].target, damageEvents[i].amount);
    }

    damageEventCount = 0;
}


void sMovement(float delta) {
    for (int i = 0; i < entity_count; i++) {
        if (entities[i].id == INVALID_ENTITY_ID) continue;
        int pos_idx = entities[i].component_indices[COMPONENT_POSITION];
        int vel_idx = entities[i].component_indices[COMPONENT_VELOCITY];
        if (pos_idx != INVALID_COMPONENT_INDEX && vel_idx != INVALID_COMPONENT_INDEX) {
            Position* pos = &((Position*)component_pools[COMPONENT_POSITION].data)[pos_idx];
            Velocity* vel = &((Velocity*)component_pools[COMPONENT_VELOCITY].data)[vel_idx];


            pos->x += vel->dx * delta;
            pos->y += vel->dy * delta;
        }
    }
}




void sRender() {
    BeginDrawing();
    ClearBackground(BLACK);
    for (int i = 0; i < entity_count; i++) {
        if (entities[i].id == INVALID_ENTITY_ID) continue;
        int pos_idx = entities[i].component_indices[COMPONENT_POSITION];
        if (pos_idx != INVALID_COMPONENT_INDEX) {
            Position* pos = &((Position*)component_pools[COMPONENT_POSITION].data)[pos_idx];


            DrawCircle((int)pos->x, (int)pos->y, 50, RED);
        }
    }
    EndDrawing();
}
