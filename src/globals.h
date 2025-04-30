#ifndef GLOBALS_H
#define GLOBALS_H

#define HEIGHT 1200.0
#define WIDTH 1600.0
#define FPS 60
#define TITLE "PIXEL ARENA"

#define MAX_ENTITIES 1000
#define MAX_EVENTS 1000
#define NUM_COMPONENT_TYPES 4
#define INVALID_ENTITY_ID -1
#define INVALID_SYSTEM -1
#define INVALID_COMPONENT_INDEX -1

typedef struct {
    int id;
    int component_indices[NUM_COMPONENT_TYPES];
} Entity;

#endif
