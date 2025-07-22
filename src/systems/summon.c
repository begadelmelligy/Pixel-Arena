#include "../../systems/summon.h"

void summon_entities(World *world, EntityType type, int num_entiteis, enum Formation formation) {}

void sSummon(World *world, float dt)
{
    (void)dt;
    EventHandler *event_handler = &world->event_handler;

    for (int i = 0; i < event_handler->count; i++) {
        Event *e = &event_handler->events[i];
        if (e->type == EVENT_SUMMON) {
            summon_entities(world, e->summon.type, e->summon.num_entities, e->summon.formation);
        }
    }
}
