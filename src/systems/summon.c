#include "../../systems/summon.h"
#include "../dev_tools/profiler.h"
#include "../ecs_core/entity.h"
#include <stdio.h>

void summon_entities(World *world, SummonEvent summon_event)
{
    printf("Summoning type: %d, Count: %d, Formation: %d, x1: %f, y1: %f, x2: %f, y2: %f, x3: %f, y3: %f\n", summon_event.type,
           summon_event.num_entities, summon_event.formation, summon_event.x[0], summon_event.y[0], summon_event.x[1], summon_event.y[1],
           summon_event.x[2], summon_event.y[2]);

    for (int i = 0; i < summon_event.num_entities; i++) {
        summon_entity_template(world, summon_event.type, summon_event.x[i], summon_event.y[i]);
    }
}

void sSummon(World *world, float dt)
{
    PROFILE_BEGIN("System Summon");

    (void)dt;

    EventHandler *event_handler = &world->event_handler;

    for (int i = 0; i < event_handler->summon_count; i++) {
        Event e = event_handler->events[i];
        summon_entities(world, e.summon);
    }
    event_handler->summon_count = 0;

    PROFILE_END("System Summon");
}
