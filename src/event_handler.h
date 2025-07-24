#ifndef EVENT_HANDLER
#define EVENT_HANDLER

#include "event_type.h"
#include "globals.h"

// Add more events here
typedef struct Event {
    SummonEvent summon;
} Event;

// Add counts for each event
typedef struct EventHandler {
    int summon_count;
    Event events[MAX_EVENTS];
} EventHandler;

void init_event_handler(EventHandler *handler);
int event_handler_push(EventHandler *handler, EventType event_type, Event event);

#endif
