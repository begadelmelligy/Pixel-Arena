#ifndef SUMMON_H
#define SUMMON_H

#include "../src/game/data/entity_data.h"
#include "../src/world.h"

typedef enum Formation {
    CIRCLE = 0,
    RECTANGLE = 1,
} Formation;

typedef struct {
    int num_entities;
    EntityType type;
    enum Formation formation;
} SummonEvent;

void queue_summon(EntityType type, int num_entities, enum Formation formation);
void apply_summon(World *world, EntityType type, int num_entiteis, enum Formation formation);
void sSummon(World *world, float dt);

#endif
