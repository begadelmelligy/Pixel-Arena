#ifndef EVENT_TYPE
#define EVENT_TYPE

#include "globals.h"

typedef enum {
    EVENT_NONE = 0,
    EVENT_SUMMON,
} EventType;

typedef struct {
    int num_entities;
    int type;
    enum Formation formation;
} SummonEvent;

#endif
