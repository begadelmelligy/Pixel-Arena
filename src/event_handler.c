#include "event_handler.h"
#include "globals.h"
#include <string.h>

void event_handler_init(EventHandler *handler)
{
    handler->count = 0;
    memset(handler->events, 0, sizeof(handler->events));
}

int event_handler_push(EventHandler *handler, Event event)
{
    if (handler->count >= MAX_EVENTS) {
        return 0;
    }
    handler->events[handler->count++] = event;
    return 1;
}
