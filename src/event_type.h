#ifndef EVENT_TYPE
#define EVENT_TYPE

#include "globals.h"

// Add more event types here
typedef enum {
    EVENT_NONE = 0,
    EVENT_SUMMON,
} EventType;

typedef struct {
    int num_entities;
    int type; // Entity Type (entity_data)
    enum Formation formation;
    float *x;
    float *y;
} SummonEvent;

#endif
