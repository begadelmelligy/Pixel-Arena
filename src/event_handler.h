#ifndef EVENT_HANDLER
#define EVENT_HANDLER

#include "../systems/summon.h"
#include "globals.h"

typedef enum {
    EVENT_SUMMON,
} EventType;

typedef struct EventHandler {
    EventType type;
    union {
        SummonEvent summon[MAX_EVENTS];
    };
} EventHandler;

#endif
