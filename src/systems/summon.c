#include "../../systems/summon.h"
#include <stdio.h>

SummonEvent summon_events[MAX_EVENTS];
int summon_event_count = 0;

void queue_summon(EntityType type, int num_entities, enum Formation formation)
{
    if (summon_event_count < MAX_EVENTS) {
        summon_events[summon_event_count++] = (SummonEvent){num_entities, type, formation};
    }
}

void apply_summon(World *world, EntityType type, int num_entiteis, enum Formation formation) {}

void sSummon(World *world, float dt)
{
    (void)dt;
    if (!world->game_state.is_paused) {
        for (int i = 0; i < summon_event_count; i++) {
            apply_summon(world, summon_events[i].num_entities, summon_events[i].type, summon_events[i].formation);
        }

        summon_event_count = 0;
    }
}
