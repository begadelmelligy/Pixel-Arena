#ifndef GLOBALS_H
#define GLOBALS_H

#include <stdint.h>

#define HEIGHT 1200.0
#define WIDTH 1600.0
#define FPS 60
#define TITLE "PIXEL ARENA"

#define MAX_ENTITIES 1000
#define MAX_EVENTS 1000

#define INVALID_ENTITY_ID -1
#define INVALID_SYSTEM -1
#define INVALID_COMPONENT_INDEX -1

#define NUM_COMPONENT_TYPES 6

/*Add more components here*/
enum ComponentType {
    COMPONENT_POSITION = 0,
    COMPONENT_VELOCITY = 1,
    COMPONENT_HEALTH = 2,
    COMPONENT_PROPERTIES = 3,
    COMPONENT_GRIDPOSITION = 4,
    COMPONENT_PATH = 5,
};

typedef uint64_t ComponentMask;

typedef struct Entity {
    int id;
    ComponentMask component_masks;
    int component_indices[NUM_COMPONENT_TYPES];
} Entity;

#endif
