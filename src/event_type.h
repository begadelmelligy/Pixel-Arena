#ifndef EVENT_TYPE
#define EVENT_TYPE

#include "globals.h"
#include "raylib.h"

// Add more event types here
typedef enum {
    EVENT_NONE = 0,
    EVENT_SUMMON,
} EventType;

typedef struct {
    int num_entities;
    int type; // Entity Type (entity_data)
    enum Formation formation;
    double *x;
    double *y;
} SummonEvent;

#endif
