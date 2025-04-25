#include "systems.h"
#include "components.h"
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
            cHealth* health = &((cHealth*)component_pools[COMPONENT_HEALTH].data)[health_idx];


            health->currentHealth -= amount;
            if (health->currentHealth < 0){
                health->currentHealth = 0;
            }
            printf("Entity %d has taken %f damage\n", entities[entity_id].id, amount);
            printf("Remaining life is %f\n\n", health->currentHealth);
        }
}

void spawnUnits(int quantity, float pos_x, float pos_y, float max_health, UnitRarity rarity, int num_types, UnitType types[num_types]) {
    for (int i = 0; i < quantity; i++) {
        int e = create_entity();
        if (e != INVALID_ENTITY_ID) {
            cPosition p = {pos_x, pos_y};
            cHealth h = {max_health, max_health};
            cProperties pr = {{0}, rarity, num_types};

            for (int j = 0; j < num_types; j++) {
                pr.types[j] = types[j];
            }

            add_component(e, COMPONENT_POSITION, &p);
            add_component(e, COMPONENT_HEALTH, &h);
            add_component(e, COMPONENT_PROPERTIES, &pr);
        }
    }

}

void sDamage(void){
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
            cPosition* pos = &((cPosition*)component_pools[COMPONENT_POSITION].data)[pos_idx];
            cVelocity* vel = &((cVelocity*)component_pools[COMPONENT_VELOCITY].data)[vel_idx];


            pos->x += vel->dx * delta;
            pos->y += vel->dy * delta;
        }
    }
}



void sRender(void) {
    BeginDrawing();
    ClearBackground(BLACK);
    for (int i = 0; i < entity_count; i++) {
        if (entities[i].id == INVALID_ENTITY_ID) continue;
        int pos_idx = entities[i].component_indices[COMPONENT_POSITION];
        if (pos_idx != INVALID_COMPONENT_INDEX) {
            cPosition* pos = &((cPosition*)component_pools[COMPONENT_POSITION].data)[pos_idx];


            DrawCircle((int)pos->x, (int)pos->y, 50, RED);
        }
    }
    EndDrawing();
}
