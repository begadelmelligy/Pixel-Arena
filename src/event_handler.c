#include "event_handler.h"
#include "event_type.h"
#include <string.h>

void init_event_handler(EventHandler *handler)
{
    handler->summon_count = 0;
    memset(handler->events, 0, sizeof(handler->events));
}

int event_handler_push(EventHandler *handler, EventType event_type, Event event)
{
    switch (event_type) {
        case EVENT_SUMMON:
            if (handler->summon_count >= MAX_EVENTS) {
                return 0;
            }
            handler->events[handler->summon_count++] = event;
            return 1;
        case EVENT_NONE:
            return 0;
    }
}
