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

#define NUM_COMPONENT_TYPES 7

/*Add more components here*/
enum ComponentType {
    COMPONENT_POSITION = 0,
    COMPONENT_VELOCITY = 1,
    COMPONENT_HEALTH = 2,
    COMPONENT_PROPERTIES = 3,
    COMPONENT_GRIDPOSITION = 4,
    COMPONENT_PATH = 5,
    COMPONENT_TARGET = 6,
};

enum EntityTag {
    TAG_NONE = 0,
    TAG_ENEMY_HERO = 1 << 0,
    TAG_PLAYER_CREEPS = 1 << 1,
    TAG_PLAYER_BOSS = 1 << 2,
    TAG_PLAYER_HERO = 1 << 3
};

typedef uint64_t ComponentMask;
typedef uint8_t TagMask;

typedef struct Entity {
    int id;
    ComponentMask component_masks;
    TagMask tag_mask;
    int component_indices[NUM_COMPONENT_TYPES];
} Entity;

#endif
