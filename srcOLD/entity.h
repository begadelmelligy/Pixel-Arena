#ifndef ENTITY_H
#define ENTITY_H

#include "globals.h"

typedef struct {
    int id;
    int component_indices[NUM_COMPONENT_TYPES];
} Entity;

#endif
