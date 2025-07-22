#ifndef EVENT_HANDLER
#define EVENT_HANDLER

#include "event_type.h"
#include "globals.h"

typedef struct Event {
    EventType type;
    union {
        SummonEvent summon;
    };
} Event;

typedef struct EventHandler {
    Event events[MAX_EVENTS];
    int count;
} EventHandler;

void event_handler_init(EventHandler *handler);
int event_handler_push(EventHandler *handler, Event event);

#endif
